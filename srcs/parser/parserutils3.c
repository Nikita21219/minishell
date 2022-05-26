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

int	rewrite_args(char ***in, char **out)
{
	int		x;
	int		y;
	char	**tmp;

	x = len(*in);
	y = len(out);
	tmp = malloc(sizeof(char *) * (x + y + 1));
	if (!tmp)
		return (1);
	x = -1;
	while ((*in)[++x])
		tmp[x] = (*in)[x];
	y = -1;
	while (out[++y])
	{
		tmp[x++] = out[y];
		out[y] = NULL;
	}
	tmp[x] = NULL;
	free (*in);
	*in = tmp;
	return (0);
}

int	move_args(t_comm **p, t_comm **tmp)
{
	char	**arg;
	int		i;

	i = 0;
	arg = (*tmp)->args;
	arg++;
	if (!(*p)->comm && arg[0])
	{
		(*p)->comm = arg[0];
		arg++;
	}
	if (*arg)
		if (rewrite_args(&(*p)->args, arg))
			return (1);
	while ((*tmp)->args[++i])
		(*tmp)->args[i] = NULL;
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
		if (((tmp->oper && tmp->oper[0] == '>') \
		|| (tmp->prev && tmp->prev->oper && tmp->prev->oper[0] == '>')) \
		|| ((tmp->oper && tmp->oper[0] == '<') \
		|| (tmp->prev && tmp->prev->oper && tmp->prev->oper[0] == '<')))
			if (move_args(p, &tmp))
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
