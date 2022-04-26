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
