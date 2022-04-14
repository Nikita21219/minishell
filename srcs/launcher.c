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

	dir_and_sep = ft_strjoin(dir, sep);
	if (!dir_and_sep)
		return (NULL);
	ptr_to_free = dir_and_sep;
	res = ft_strjoin(dir_and_sep, comm);
	free(ptr_to_free);
	free_arrs(dirs);
	return (res);
}

char	*get_path(char *comm)
{
	char	**dirs;
	char	*correct_dir;
	DIR		*dir;
	int		i;
	int		status;

	dirs = ft_split(getenv("PATH"), ':');
	if (!dirs)
		return (NULL);
	i = -1;
	status = is_correct_comm(comm, dirs);
	if (status < 0)
		return (NULL);
	if (comm && comm[0] == '/' && status)
	{
		free_arrs(dirs);
		return (ft_strdup(comm));
	}
	while (dirs[++i])
	{
		correct_dir = NULL;
		dir = opendir(dirs[i]);
		if (!dir)
			return (NULL);
		if (read_directory(dir, comm))
			correct_dir = dirs[i];
		if (closedir(dir) == -1)
			return (NULL);
		if (correct_dir)
			return (three_str_join(correct_dir, "/", comm, dirs));
	}
	return ("dir not found");
}

int	executor(t_comm *data, char *path, char **env, int count_comm)
{
	int	pid;

	if (is_same_lines(data->oper, "|") || is_same_lines(data->oper, "<<"))
	{
		if (create_pipe(data))
			return (PIPE_ERR);
		if (is_same_lines(data->oper, "<<"))
			if (heredoc(data))
				return (MALLOC_ERR);
	}
	else if (data->next && is_same_lines(data->next->oper, "|") && is_same_lines(data->oper, "<<"))
		if (create_pipe(data->next))
			return (PIPE_ERR);
	pid = fork();
	if (pid < 0)
		return (FORK_ERR);
	else if (pid == 0)
	{
		if (is_same_lines(data->oper, ">") || is_same_lines(data->oper, ">>"))
		{
			if (redirect(data) == DUP_ERR)
				return (DUP_ERR);
		}
		else if (is_same_lines(data->oper, "|") || (data->prev && is_same_lines(data->prev->oper, "|")))
		{
			if (duplicate_fd(data, data->i, count_comm))
				return (DUP_ERR);
		}
		else if (is_same_lines(data->oper, "<<"))
		{
			if (duplicate_fd_for_heredoc(data) == DUP_ERR)
				return (DUP_ERR);
			if (data->next && is_same_lines(data->next->oper, "|"))
				if (duplicate_fd(data->next, data->next->i, count_comm))
					return (DUP_ERR);
		}
		if (data->comm)
		{
			if (data->prev && data->prev->prev && is_same_lines(data->prev->prev->oper, "<<"))
				if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
					return (DUP_ERR);
			if (close_fd(data))
				return (CLOSE_ERR);
			if (execve(path, data->args, env) == -1)
				return (EXEC_ERR);
		}
		else
			exit(0);
	}
	free(path);
	return (0);
}

int	launcher(t_comm *data, char **env)
{
	char	*path;
	int		count_command;
	int		wait_count;
	int		error;
	t_comm	*tmp_dt;

	tmp_dt = data;
	wait_count = 0;
	count_command = get_count_comm(data);
	if (count_command == 0)
		return (0);
	while (data)
	{
		path = get_path(data->comm);
		if (!path && data->comm)
			return (continue_with_print("Error: memory allocated failed\n"));
		if (is_same_lines(path, "dir not found") && !is_same_lines(data->oper, "<<") && !is_same_lines(data->oper, ">")) //TODO start builtins
		{
			printf("dir not found\n");
			return (0);
		}
		else
		{
			wait_count++;
			error = executor(data, path, env, count_command);
			if (error < 0)
				return (handle_error_executor(error));
		}
		if (is_same_lines(data->oper, "<<") || is_same_lines(data->oper, ">") || is_same_lines(data->oper, ">>"))
			data = data->next->next;
		else
			data = data->next;
	}
	if (close_fd(tmp_dt))
		return (continue_with_print("Error: close() returned fail\n"));
	while (wait_count-- > 0)
	{
		if (wait(NULL) == -1)
			return (continue_with_print("Error: wait() returned fail\n"));
	}
	return (0);
}
