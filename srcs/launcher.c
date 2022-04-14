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

	dirs = ft_split(getenv("PATH"), ':');
	if (!dirs)
		return (NULL);
	i = -1;
	if (comm && comm[0] == '/' && is_correct_comm(comm))
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
	return (ft_strdup("launch builtins"));
}

int	executor(t_data *data, char *path, char **env, int count_comm)
{
	int	pid;

	if (is_same_lines(data->comm->oper, "|") || is_same_lines(data->comm->oper, "<<"))
	{
		if (create_pipe(data->comm))
			return (PIPE_ERR);
		if (is_same_lines(data->comm->oper, "<<"))
			if (heredoc(data->comm))
				return (MALLOC_ERR);
	}
	if ((data->comm->next && is_same_lines(data->comm->next->oper, "|") && is_same_lines(data->comm->oper, "<<")) || (is_same_lines(data->comm->oper, "<")))
	{
		if (create_pipe(data->comm->next))
			return (PIPE_ERR);
	}
	pid = fork();
	if (pid < 0)
		return (FORK_ERR);
	else if (pid == 0)
	{
		if (is_same_lines(data->comm->oper, ">") || is_same_lines(data->comm->oper, ">>"))
		{
			if (redirect_out(data->comm) == DUP_ERR)
				return (DUP_ERR);
		}
		else if (is_same_lines(data->comm->oper, "<"))
		{
			if (redirect_in(data->comm) == DUP_ERR)
				return (DUP_ERR);
		}
		else if (is_same_lines(data->comm->oper, "|") || (data->comm->prev && is_same_lines(data->comm->prev->oper, "|")))
		{
			if (duplicate_fd(data->comm, data->comm->i, count_comm))
				return (DUP_ERR);
		}
		else if (is_same_lines(data->comm->oper, "<<"))
		{
			if (duplicate_fd_for_heredoc(data->comm) == DUP_ERR)
				return (DUP_ERR);
			if (data->comm->next && is_same_lines(data->comm->next->oper, "|"))
				if (duplicate_fd(data->comm->next, data->comm->next->i, count_comm))
					return (DUP_ERR);
		}
		if (data->comm->comm)
		{
			if (data->comm->prev && data->comm->prev->prev && is_same_lines(data->comm->prev->prev->oper, "<<"))
				if (dup2(data->comm->prev->fd[0], STDIN_FILENO) == -1)
					return (DUP_ERR);
			if (close_fd(data->comm))
				return (CLOSE_ERR);
			if (is_same_lines("launch builtins", path))
			{
				if (launch_builtins(data))
					exit(1);
				exit(0);
			}
			else
			{
				if (execve(path, data->comm->args, env) == -1)
					return (EXEC_ERR);
			}
		}
		else
			exit(0);
	}
	free(path);
	return (0);
}

int	launcher(t_data *data, char **env)
{
	char	*path;
	int		count_command;
	int		wait_count;
	int		error;
	t_comm	*tmp_dt;

	tmp_dt = data->comm;
	wait_count = 0;
	count_command = get_count_comm(data->comm);
	if (count_command == 0)
		return (0);
	while (data->comm)
	{
		if (is_builtins_in_main_proc(data->comm->comm))
		{
			launch_builtins(data);
			data->comm = data->comm->next;
			continue ;
		}
		if (is_builtins(data->comm->comm)) //TODO start builtins
			path = ft_strdup("launch builtins");
		else
			path = get_path(data->comm->comm);
		if (!path && data->comm->comm)
			return (continue_with_print("Error: memory allocated failed\n"));
		wait_count++;
		error = executor(data, path, env, count_command);
		if (error < 0)
			return (handle_error_executor(error));
		if (is_same_lines(data->comm->oper, "<<") || is_same_lines(data->comm->oper, ">") || is_same_lines(data->comm->oper, ">>") || is_same_lines(data->comm->oper, "<"))
			data->comm = data->comm->next->next;
		else
			data->comm = data->comm->next;
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
