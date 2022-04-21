#include "../includes/minishell.h"

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

int	close_fds_and_waiting(t_comm *data, int wait_count)
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
			errno = status_code;
		}
	}
	return (0);
}

int	check_builtins(t_data *data, char **path)
{
	int	error;

	if (is_builtins_in_main_proc(data->comm->comm))
	{
		error = launch_builtins(data);
		if (error)
			return (error);
		data->comm = data->comm->next;
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
	if (is_same_lines(data->comm->oper, ">") || is_same_lines(data->comm->oper, ">>"))
	{
		while (data->comm && (is_same_lines(data->comm->oper, ">") || is_same_lines(data->comm->prev->oper, ">")))
			data->comm = data->comm->next;
	}
	else if (is_same_lines(data->comm->oper, "<"))
	{
		while ((data->comm && is_same_lines(data->comm->oper, "<")) || (data->comm && is_same_lines(data->comm->prev->oper, "<")))
			data->comm = data->comm->next;
	}
	else if (data && data->comm && is_same_lines(data->comm->oper, "<<"))
	{
		while ((data->comm && is_same_lines(data->comm->oper, "<<")) || (data->comm && is_same_lines(data->comm->prev->oper, "<<")))
			data->comm = data->comm->next;
	}
	else
		data->comm = data->comm->next;
	free(path);
}

int	launcher(t_data *data, char **env)
{
	char	*path;
	int		count_command;
	int		wait_count;
	int		result;
	t_comm	*tmp_dt;

	tmp_dt = data->comm;
	wait_count = 0;
	count_command = get_count_comm(data->comm);
	if (count_command == 0)
		return (0);
	while (data->comm)
	{
		if (check_builtins(data, &path))
			continue ;
		wait_count++;
		result = executor(data, path, env, count_command);
		if (result < 0)
			return (handle_error_executor(result));
		else if (result == 1)
			return (handle_error_executor(result));
		set_next_ptr_data_and_free_path(data, path);
	}
	result = close_fds_and_waiting(tmp_dt, wait_count);
	free_lists(tmp_dt);
	return (result);
}
