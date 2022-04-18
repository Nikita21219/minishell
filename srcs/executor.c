#include "../includes/minishell.h"

int	check_redirect(t_data *data)
{
	if (is_same_lines(data->comm->oper, ">"))
		return (1);
	if (is_same_lines(data->comm->oper, ">>"))
		return (1);
	return (0);
}

int	check_pipe(t_data *data)
{
	if (is_same_lines(data->comm->oper, "|"))
		return (1);
	if (data->comm->prev && is_same_lines(data->comm->prev->oper, "|"))
		return (1);
	return (0);
}

int	handle_oper(t_data *data, int count_comm)
{
	if (check_redirect(data))
	{
		if (redirect_out(data->comm) == DUP_ERR)
			return (DUP_ERR);
	}
	else if (is_same_lines(data->comm->oper, "<"))
	{
		if (redirect_in(data->comm) == DUP_ERR)
			return (DUP_ERR);
	}
	else if (check_pipe(data))
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
	return (0);
}

void	exec_command(t_data *data, char *path, char **env)
{
	if (data->comm->prev && data->comm->prev->prev \
	&& is_same_lines(data->comm->prev->prev->oper, "<<"))
		if (dup2(data->comm->prev->fd[0], STDIN_FILENO) == -1)
			exit(DUP_ERR);
	if (close_fd(data->comm))
		exit(CLOSE_ERR);
	if (is_same_lines("launch builtins", path))
	{
		if (launch_builtins(data))
			exit(127);
		exit(0);
	}
	else
		if (execve(path, data->comm->args, env) == -1)
			exit(EXEC_ERR);
}

int	executor(t_data *data, char *path, char **env, int count_comm)
{
	int		error;

	error = check_oper(data);
	if (error)
		return (error);
	data->comm->pid = fork();
	if (data->comm->pid < 0)
		return (FORK_ERR);
	else if (data->comm->pid == 0)
	{
		error = handle_oper(data, count_comm);
		if (error)
			exit(error);
		if (data->comm->comm)
			exec_command(data, path, env);
		else
			exit(0);
	}
	return (0);
}
