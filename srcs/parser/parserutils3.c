#include "../../includes/minishell.h"

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
	if ((((*tmp)->oper && (*tmp)->oper[0] == '>') \
	|| ((*tmp)->prev && (*tmp)->prev->oper && (*tmp)->prev->oper[0] == '>')) \
	|| (((*tmp)->oper && (*tmp)->oper[0] == '<') \
	|| ((*tmp)->prev && (*tmp)->prev->oper && (*tmp)->prev->oper[0] == '<')))
	{
		arg = (*tmp)->args;
		arg++;
		if (!(*p)->comm && arg[0])
		{
			(*p)->comm = arg[0];
			arg++;
		}
		if (*arg && (*tmp)->prev)
			if (rewrite_args(&(*p)->args, arg))
				return (1);
		while ((*tmp)->args[++i] && (*tmp)->prev)
			(*tmp)->args[i] = NULL;
	}
	return (0);
}

int	checkallcommands(t_comm **p)
{
	t_comm	*tmp;

	tmp = *p;
	if (!tmp->comm && !tmp->args[1] && !tmp->oper)
		return (0);
	while (tmp)
	{
		if (tmp->oper && tmp->oper[0] != '<' \
		&& tmp->oper[0] != '>' && (!tmp->next || !tmp->comm))
		{
			if (!tmp->comm)
				printf("🔥mini_hell🔥: syntax error near unexpected token `%s'\n"\
				, tmp->oper);
			else
				printf("🔥mini_hell🔥: syntax error: unexpected end of file\n");
			errno = 258;
			return (1);
		}
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
