#include "../../includes/minishell.h"

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
	int		err;

	dt = data->comm;
	if (is_same_lines(dt->oper, "|") || is_same_lines(dt->oper, "<<"))
	{
		err = exec_heredoc_and_pipes(&dt);
		if (err)
			return (err);
	}
	if (check_operator(dt))
	{
		if (is_same_lines(dt->oper, "<") && \
		dt->next && access(dt->next->comm, 0))
		{
			write(2, "mini_hell: ", 11);
			perror(dt->next->comm);
			return (1);
		}
		if (is_same_lines(dt->oper, "<") && \
		dt->next && access(dt->next->comm, 4))
		{
			perror(dt->next->comm);
			return (1);
		}
		if (create_pipe(dt->next))
			return (PIPE_ERR);
	}
	return (0);
}
