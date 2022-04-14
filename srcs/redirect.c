#include "../includes/minishell.h"

int	redirect(t_comm *data)
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
