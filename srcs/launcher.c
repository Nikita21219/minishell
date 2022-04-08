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

char	*three_str_join(char *dir, char *sep, char *comm, char **dirs)
{
	char	*res;
	char	*dir_and_sep;
	char	*ptr_to_free;

	dir_and_sep = ft_strjoin(dir, sep); //FIXME
	if (!dir_and_sep)
		return (NULL);
	ptr_to_free = dir_and_sep;
	res = ft_strjoin(dir_and_sep, comm); //FIXME
	free(ptr_to_free);
	free_arrs(dirs);
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
	if (comm && comm[0] == '/' && is_correct_comm(comm, dirs))
	{
		free_arrs(dirs);
		return (ft_strdup(comm));
	}
	while (dirs[++i])
	{
		correct_dir = NULL;
		dir = opendir(dirs[i]);
		if (!dir)
			exit_from_minishell(); //FIXME need free dirs
		if (read_directory(dir, comm))
			correct_dir = dirs[i];
		if (closedir(dir))
			exit_from_minishell(); //FIXME need free dirs
		if (correct_dir)
		{
			return (three_str_join(correct_dir, "/", comm, dirs));
		}
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
			printf("FAIL dup2 4 %d\n", errno);
			exit(1); //FIXME
		}
	}
	return (0);
}

int	create_pipe(t_comm *data)
{
	if (pipe(data->fd) == -1)
		return (1);
	return (0);
}

int	executor(t_comm *data, char *path, char **env, int count_comm)
{
	int			pid;
	static int	i = 0;

	i++;
	if (is_same_lines(data->oper, "|"))
		create_pipe(data);
	pid = fork();
	if (pid < 0)
	{
		printf("FAIL fork %d\n", errno);
		exit(1); //FIXME
	}
	else if (pid == 0)
	{
		if (is_same_lines(data->oper, "|") || (data->prev && is_same_lines(data->prev->oper, "|")))
		{
			duplicate_fd(data, data->i, count_comm); //FIXME need handle if dup2 returned negative digit
			close_fd(data);
		}
		if (execve(path, data->args, env) == -1)
		{
			printf(TERM_YELLOW "FAIL execve %d\n", errno);
			exit(1); //FIXME
		}
	}
	free(path);
	return (i);
}

void	launcher(t_comm *data, char **env)
{
	char	*path;
	int		count_command;
	int		wait_count;
	t_comm	*tmp_dt;

	tmp_dt = data;
	wait_count = 0;
	count_command = get_count_comm(data);
	if (count_command == 0)
		return ;
	while (data)
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
			wait_count = executor(data, path, env, count_command);
		data = data->next;
	}
	close_fd(tmp_dt);
	while (wait_count-- > 0)
		wait(NULL);
}

// cat test.txt | grep developer | wc
// cat test.txt | grep developer
