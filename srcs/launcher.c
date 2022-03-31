#include "../includes/minishell.h"

int	read_directory(DIR *dir, char *command)
{
	struct dirent	*sd;

	sd = readdir(dir);
	while (sd)
	{
		if (is_same_lines(sd->d_name, command))
			return (1);
		sd = readdir(dir);
	}
	return (0);
}

char	*three_str_join(char *dir, char *sep, char *comm)
{
	char	*res;
	char	*dir_and_sep;

	dir_and_sep = ft_strjoin(dir, sep);
	if (!dir_and_sep)
		return (NULL);
	res = ft_strjoin(dir_and_sep, comm);
	if (!res)
		return (NULL);
	return (res);
}

char	*get_path(char *comm)
{
	char	**dirs;
	char	*correct_dir;
	DIR		*dir;
	int		i;

	dirs = ft_split(getenv("PATH"), ':');
	if (!dirs)
		exit_from_minishell(); //FIXME
	i = -1;
	while (dirs[++i])
	{
		correct_dir = NULL;
		dir = opendir(dirs[i]);
		if (!dir)
			exit_from_minishell(); //FIXME
		if (read_directory(dir, comm))
			correct_dir = dirs[i];
		if (closedir(dir))
			exit_from_minishell(); //FIXME
		if (correct_dir)
			return (three_str_join(correct_dir, "/", comm));
	}
	return ("dir not found");
}

int	duplicate_fd(t_comm *data, int idx, int count_comm)
{
	if (idx == 0)
	{
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			printf("FAIL dup2 1 %d\n", errno);
			exit(1); //FIXME
		}
	}
	else if (idx + 1 == count_comm)
	{
		if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
		{
			printf("FAIL dup2 2 %d\n", errno);
			exit(1); //FIXME
		}
	}
	else
	{
		if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
		{
			printf("FAIL dup2 3 %d\n", errno);
			exit(1); //FIXME
		}
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			printf("FAIL dup2 4%d\n", errno);
			exit(1); //FIXME
		}
	}
	return (0);
}

void	executor(t_comm *data, char *path, char **env, int count_comm)
{
	static int	i = 0;
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		printf("FAIL fork %d\n", errno);
		exit(1); //FIXME
	}
	else if (pid == 0)
	{
		duplicate_fd(data, i, count_comm);
		// close_fd(data);
		if (execve(path, data->args, env) == -1)
		{
			printf(TERM_YELLOW "FAIL execve %d\n", errno);
			exit(1); //FIXME
		}
	}
	i++;
	close_fd(data);
	waitpid(pid, NULL, 0);
}

void	tmp_test_func(t_comm *data, char **env)
{
	(void) env;

	int pid = fork();
	if (pid < 0)
	{
		printf("FAIL fork %d\n", errno);
		exit(1); //FIXME
	}
	else if (pid == 0)
	{
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
		{
			printf("ERRROR");
			exit(2); //FIXME
		}
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			printf("ERRROR");
			exit(3); //FIXME
		}
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->next->fd[0]);
		close(data->next->fd[1]);
		if (execve("/bin/cat", data->args, env) == -1)
		{
			printf("ERRROR exec");
			exit(4); //FIXME
		}
	}

	int pid2 = fork();
	if (pid2 < 0)
	{
		printf("FAIL fork %d\n", errno);
		exit(1); //FIXME
	}
	else if (pid2 == 0)
	{
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
		{
			printf("ERRROR");
			exit(2); //FIXME
		}
		if (dup2(data->next->fd[1], STDOUT_FILENO) == -1)
		{
			printf("ERRROR");
			exit(2); //FIXME
		}
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->next->fd[0]);
		close(data->next->fd[1]);
		if (execve("/usr/bin/grep", data->next->args, env) == -1)
		{
			printf("ERRROR exec");
			exit(4); //FIXME
		}
	}

	int pid3 = fork();
	if (pid3 < 0)
	{
		printf("FAIL fork %d\n", errno);
		exit(1); //FIXME
	}
	else if (pid3 == 0)
	{
		if (dup2(data->next->fd[0], STDIN_FILENO) == -1)
		{
			printf("ERRROR");
			exit(2); //FIXME
		}
		close(data->fd[0]);
		close(data->fd[1]);
		close(data->next->fd[0]);
		close(data->next->fd[1]);
		if (execve("/usr/bin/wc", data->next->next->args, env) == -1)
		{
			printf("ERRROR exec");
			exit(4);
		}
	}
	close(data->fd[0]);
	close(data->fd[1]);
	close(data->next->fd[0]);
	close(data->next->fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	waitpid(pid3, NULL, 0);
}

void	launcher(t_comm *data, char **env)
{
	char	*path;
	int		count_command;

	count_command = get_count_comm(data);
	if (count_command == 0)
		return ;
	if (push_fds_in_data(data))
		exit_from_minishell(); //FIXME
	// tmp_test_func(data, env);
	// exit(0)
	while (data && is_same_lines("|", data->oper))
	{
		path = get_path(data->comm);
		if (!path)
			exit_from_minishell(); //FIXME
		if (is_same_lines(path, "dir not found"))
		{
			printf("dir not found\n");
			return ;
		}
		else
			executor(data, path, env, count_command);
		data = data->next;
	}
}

// cat test.txt | grep developer | wc
// cat test.txt | grep developer
