#include "../includes/minishell.h"

int handle_oper(t_data *data, int count_comm)
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
	return (0);
}
