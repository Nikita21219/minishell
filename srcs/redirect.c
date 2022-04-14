#include "../includes/minishell.h"

int	redirect_out(t_comm *data)
{
	int	fd;

	if (is_same_lines(data->oper, ">"))
		fd = open(data->next->comm, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		fd = open(data->next->comm, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd == -1)
		return (OPEN_ERR);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (DUP_ERR);
	if (data->prev && is_same_lines(data->prev->oper, "|"))
		if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
			return (DUP_ERR);
	return (0);
}

int	redirect_in(t_comm *data)
{
	int	fd;

	fd = open(data->next->comm, O_RDONLY);
	if (fd == -1)
		return (OPEN_ERR);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (DUP_ERR);
	if (data->next && is_same_lines(data->next->oper, "|"))
		if (dup2(data->next->fd[1], STDOUT_FILENO) == -1)
			return (DUP_ERR);
	return (0);
}
