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
		exit_from_minishell(); //TODO fix
	i = -1;
	while (dirs[++i])
	{
		correct_dir = NULL;
		dir = opendir(dirs[i]);
		if (!dir)
			exit_from_minishell(); //TODO fix
		if (read_directory(dir, comm))
			correct_dir = dirs[i];
		if (closedir(dir))
			exit_from_minishell(); //TODO fix
		if (correct_dir)
			return (three_str_join(correct_dir, "/", comm));
	}
	return ("dir not found");
}

void	executor(t_comm *data, char *path, char **env)
{
	// char	**commands;
	// char	**args;
	// char	*buf;
	static int	i = 0;
	int			pid;

	pid = fork();
	if (pid < 0)
	{
		printf("FAIL fork %d\n", errno);
		exit(1); //TODO fix
	}
	else if (pid == 0)
	{
		if (dup2(data->fd[i], STDIN_FILENO) == -1)
		{
			printf("FAIL dup2 %d\n", errno);
			exit(1); //TODO fix
		}
		if (dup2(data->fd[i + 1], STDOUT_FILENO) == -1)
		{
			printf("FAIL dup2 %d\n", errno);
			exit(1); //TODO fix
		}
		close(data->fd[i]);
		close(data->fd[i + 1]);
		i += 2;
		if (execve(path, data->args, env) == -1)
		{
			printf(TERM_YELLOW "FAIL execve %d\n", errno);
			exit(1); //TODO fix
		}
	}
	waitpid(pid, NULL, 0);

	// int	pid2 = fork();
	// if (pid2 < 0)
	// {
	// 	printf("FAIL fork %d\n", errno);
	// 	exit(1); //TODO fix
	// }
	// else if (pid2 == 0)
	// {
	// 	if (dup2(fd[0], STDIN_FILENO) == -1)
	// 	{
	// 		printf("FAIL dup2 %d\n", errno);
	// 		exit(1); //TODO fix
	// 	}
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	if (execve(get_path(data->next->comm), data->next->args, env))
	// 	{
	// 		printf(TERM_YELLOW "FAIL execve %d\n", errno);
	// 		exit(1); //TODO fix
	// 	}
	// }
	// close(fd[0]);
	// close(fd[1]);
	// waitpid(pid2, NULL, 0);
	// waitpid(pid, NULL, 0);
}

void	launcher(t_comm *data, char **env)
{
	char	*path;
	int		*fd;
	int		count_command;

	count_command = get_cout_comm(data);
	if (count_command == 0)
		return ;
	fd = malloc(sizeof(int) * count_command);
	data->fd = fd;
	if (!fd)
		exit_from_minishell(); //TODO fix
	if (create_pipes(&fd, count_command))
		exit_from_minishell(); //TODO fix
	path = get_path(data->comm);
	if (!path)
		exit_from_minishell(); //TODO fix
	while (data && is_same_lines("|", data->oper))
	{
		if (is_same_lines(path, "dir not found"))
		{
			printf("dir not found\n");
			return ;
		}
		else
			executor(data, path, env);
		data = data->next;
	}
}

// cat test.txt | grep developer | wc
// cat test.txt | grep developer
