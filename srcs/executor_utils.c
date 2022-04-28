#include "../includes/minishell.h"

int	check_redirect(t_data *data)
{
	if (is_same_lines(data->comm->oper, ">"))
		return (1);
	if (is_same_lines(data->comm->oper, ">>"))
		return (1);
	return (0);
}

int	init_result(char **free_ptr, char **nl, char **line, char **res)
{
	*free_ptr = *res;
	*res = ft_strjoin(*res, *nl);
	free(*nl);
	free(*free_ptr);
	if (*res == NULL)
	{
		free(*line);
		return (1);
	}
	return (0);
}

int	check_operator(t_comm *dt)
{
	if (dt->next)
	{
		if (is_same_lines(dt->next->oper, "|") && (is_same_lines(dt->oper, "<<") || is_same_lines(dt->oper, "<")))
			return (1);
	}
	if (is_same_lines(dt->oper, "<") || is_same_lines(dt->oper, ">"))
		return (1);
	return (0);
}

int	exec_heredoc_and_pipes(t_comm **data)
{
	t_comm	*dt;

	dt = *data;
	if (create_pipe(dt))
		return (PIPE_ERR);
	while (dt && is_same_lines(dt->oper, "<<"))
	{
		if (heredoc(dt))
			return (MALLOC_ERR);
		dt = dt->next;
	}
	return (0);
}

int	next_oper(char *oper)
{
	// if (is_same_lines(oper, "<"))
	// 	return (1);
	if (is_same_lines(oper, ">"))
		return (1);
	if (is_same_lines(oper, "<<"))
		return (1);
	if (is_same_lines(oper, "|"))
		return (1);
	return (0);
}

int	curr_oper(char *oper)
{
	if (is_same_lines(oper, "<"))
		return (1);
	// if (is_same_lines(oper, "<<"))
	// 	return (1);
	return (0);
}
