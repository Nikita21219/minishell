#include "../../includes/minishell.h"

void	move_list(t_comm **p)
{
	t_comm	*temp;
	char	**tmp_arg;
	int		i;

	i = 0;
	temp = (*p)->next;
	tmp_arg = (*p)->args;
	(*p)->args = temp->args;
	temp->args = tmp_arg;
	(*p)->comm = (*p)->args[1];
	while ((*p)->args[++i])
		(*p)->args[i] = (*p)->args[i + 1];
}

int	move_args(t_comm **arg, int i, int x)
{
	char	**tmp;

	i = len((*arg)->args);
	x = len((*arg)->next->args);
	tmp = malloc(sizeof(char *) * (i + x + 1));
	if (!tmp)
	{
		errno = 12;
		printf("Parse error malloc\n");
		return (1);
	}
	i = -1;
	x = 0;
	while ((*arg)->args[++i])
		tmp[i] = (*arg)->args[i];
	while ((*arg)->next->args[++x])
	{
		tmp[i++] = (*arg)->next->args[x];
		(*arg)->next->args[x] = NULL;
	}
	tmp[i] = NULL;
	free((*arg)->args);
	(*arg)->args = tmp;
	return (0);
}

int	checkallcommands(t_comm **p)
{
	t_comm	*tmp;

	tmp = *p;
	if ((*p) && (*p)->next && !(*p)->prev && !(*p)->comm && \
		((*p)->oper[0] == '<' || (*p)->oper[0] == '>'))
		move_list(p);
	while (tmp)
	{
		if ((!tmp->comm && !(is_same_lines(tmp->oper, ">") || \
		is_same_lines(tmp->oper, ">>") || is_same_lines(tmp->oper, "<") \
		|| is_same_lines(tmp->oper, "<<"))) || (tmp->oper && !tmp->next))
		{
			printf("Parse error\n");
			errno = 22;
			return (1);
		}
		if (tmp && tmp->next && tmp->oper[0] == '>')
			if (move_args(&tmp, 0, 0))
				return (1);
		if (check_wildcard(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	vars_quote_check(char **str, char **s, int i, t_comm *data)
{
	char	quote;

	if ((*s)[i] == '$' && data->prev && is_same_lines(data->prev->oper, "<<"))
		return (++i);
	if ((*s)[i] == '$' && (*s)[i + 1] && !ft_space((*s)[i + 1]) \
		&& (*s)[i + 1] != '=')
		return (takevar(s, str, data, i));
	if ((*s)[i] == 34 || (*s)[i] == 39)
	{
		quote = (*s)[i];
		if (check_second_qoute(*s, i, quote))
		{
			if (write_arg(str, s, i))
				return (-1);
			(*s)++;
			i = check_quote(s, str, quote, data);
			if (i < 0)
				return (-1);
			i = -1;
			(*s)++;
		}
	}
	if ((*s)[i] == '*')
		(*s)[i] = '*' * -1;
	return (++i);
}
