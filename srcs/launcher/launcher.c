#include "../../includes/minishell.h"

char	*get_path(char *comm)
{
	char	**dirs;
	char	*correct_dir;
	char	*result;
	int		i;

	if (is_correct_comm(comm))
		return (ft_strdup(comm));
	i = -1;
	if (initialize_dirs(&dirs))
		return (NULL);
	while (dirs[++i])
	{
		correct_dir = ft_strjoin(dirs[i], "/");
		result = ft_strjoin(correct_dir, comm);
		free(correct_dir);
		if (!access(result, 1))
		{
			free_arrs(dirs);
			return (result);
		}
		free(result);
	}
	free_arrs(dirs);
	return (ft_strdup("launch builtins"));
}

int	close_fds_and_waiting(t_comm *data, int wait_count, t_data *dt)
{
	int	wstatus;
	int	status_code;

	if (close_fd(data))
		return (continue_with_print("Error: close() returned fail\n"));
	while (wait_count-- > 0)
	{
		if (wait(&wstatus) == -1)
			return (continue_with_print("Error: wait() returned fail\n"));
		if (WIFEXITED(wstatus))
		{
			status_code = WEXITSTATUS(wstatus);
			// fprintf(stderr, "status_code = %d\n", status_code); //FIXME tmp line for debug. need to delete
			errno = status_code;
		}
	}
	if (is_same_lines(data->comm, "export") && data->args[1])
		set_env(data, dt); //FIXME if fail
	return (0);
}

int	check_builtins(t_data *data, char **path)
{
	int	error;

	if (is_builtins_in_main_proc(data->comm->comm))
	{
		error = launch_builtins(data);
		data->comm = data->comm->next;
		if (error)
			return (error);
		return (-1);
	}
	else if (is_builtins(data->comm->comm))
		*path = ft_strdup("launch builtins");
	else
		*path = get_path(data->comm->comm);
	if (!(*path) && data->comm->comm)
		return (continue_with_print("Error: memory allocated failed\n"));
	return (0);
}

void	set_next_ptr_data_and_free_path(t_data *data, char *path)
{
	if (data->comm && (is_same_lines(data->comm->oper, ">") || \
	is_same_lines(data->comm->oper, ">>") || \
	is_same_lines(data->comm->oper, "<<") || \
	is_same_lines(data->comm->oper, "<")))
	{
		while ((data->comm && (is_same_lines(data->comm->oper, ">") || \
		is_same_lines(data->comm->oper, "<<") || \
		is_same_lines(data->comm->oper, ">>") || \
		is_same_lines(data->comm->oper, "<"))) || \
		(data->comm && data->comm->prev && \
		(is_same_lines(data->comm->prev->oper, ">") \
		|| is_same_lines(data->comm->prev->oper, ">>") \
		|| is_same_lines(data->comm->prev->oper, "<"))))
		{
			if (is_same_lines(data->comm->oper, "<<"))
				while ((data->comm && is_same_lines(data->comm->oper, "<<")) || \
				(data->comm && is_same_lines(data->comm->prev->oper, "<<")))
					data->comm = data->comm->next;
			else
				data->comm = data->comm->next;
		}
	}
	else
		data->comm = data->comm->next;
	free(path);
}

int	get_fsize(int fd)
{
	struct stat	buff;

	if (fstat(fd, &buff) == -1)
		return (-1);
	return (buff.st_size);
}

void	set_env(t_comm *data, t_data *dt)
{
	char	*buf;
	char	**split_str;
	int		i;

	buf = malloc(get_fsize(data->fd[0]) * sizeof(char));
	if (read(data->fd[0], buf, get_fsize(data->fd[0])) == -1)
		fprintf(stderr, "ERROR\n"); //FIXME fprintf is not allow
	split_str = ft_split(buf, '\n'); //FIXME if rerurned fail
	free(buf);
	delenv(&dt->env);
	dt->env = NULL;
	take_start_env(dt, split_str);
	i = -1;
	while (split_str[++i])
		free(split_str[i]);
	free(split_str);
}

int	launcher(t_data *data)
{
	char	*path;
	int		count_command;
	int		wait_count;
	int		result;
	t_comm	*tmp_dt;

	if (init_var(&tmp_dt, data, &wait_count, &count_command))
		return (0);
	while (data->comm)
	{
		if (check_builtins(data, &path))
			continue ;
		wait_count++;
		result = executor(data, path, count_command);
		if (result < 0 || result == 1)
			return (handle_error_executor(result));
		set_next_ptr_data_and_free_path(data, path);
	}
	result = close_fds_and_waiting(tmp_dt, wait_count, data);
	// delcommand(&tmp_dt);
	return (result);
}
