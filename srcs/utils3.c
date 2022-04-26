#include "../includes/minishell.h"

int	create_pipe(t_comm *data)
{
	if (pipe(data->fd) == -1)
		return (1);
	return (0);
}

int	is_redirect(char *op)
{
	if (is_same_lines(op, "<<"))
		return (1);
	if (is_same_lines(op, ">>"))
		return (1);
	if (is_same_lines(op, "<"))
		return (1);
	if (is_same_lines(op, ">"))
		return (1);
	return (0);
}

int	duplicate_fd(t_comm *data, int idx, int count_comm)
{
	if (idx == 0)
	{
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			return (1);
	}
	else if (idx + 1 == count_comm)
	{
		if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
			return (1);
	}
	else
	{
		if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
			return (1);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			return (1);
	}
	return (0);
}

int	initialize_dirs(char ***dirs)
{
	*dirs = ft_split(getenv("PATH"), ':');
	if (!(*dirs))
		return (1);
	return (0);
}

int	check_oper(t_data *data)
{
	t_comm	*dt;

	dt = data->comm;
	if (is_same_lines(dt->oper, "|") || is_same_lines(dt->oper, "<<"))
	{
		if (create_pipe(dt))
			return (PIPE_ERR);
		while (dt && is_same_lines(dt->oper, "<<"))
		{
			if (heredoc(dt))
				return (MALLOC_ERR);
			dt = dt->next;
		}
	}
	if ((dt->next && is_same_lines(dt->next->oper, "|") \
	&& is_same_lines(dt->oper, "<<")) \
	|| is_same_lines(dt->oper, "<") || is_same_lines(dt->oper, ">"))
	{
		if (is_same_lines(dt->oper, "<") && \
		dt->next && access(dt->next->comm, 0))
			return (1);
		if (create_pipe(dt->next))
			return (PIPE_ERR);
	}
	return (0);
}
