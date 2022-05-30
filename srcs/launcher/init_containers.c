#include "../../includes/minishell.h"

int	is_logic_oper(char *str)
{
	if (is_same_lines("&&", str))
		return (1);
	if (is_same_lines("||", str))
		return (2);
	return (0);
}

int	add_new_container(t_comm **data, t_box **box)
{
	t_box	*new;
	t_box	*p;
	t_comm	*start;

	p = *box;
	while (p->next)
		p = p->next;
	new = malloc(sizeof(t_box));
	if (!new)
		return (1);
	new->oper = (*data)->oper;
	(*data)->oper = NULL;
	start = (*data)->next;
	(*data)->next = NULL;
	(*data) = start;
	new->dt_comm = start;
	new->dt_comm->prev = NULL;
	new->next = NULL;
	p->next = new;
	return (0);
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

int	init_containers(t_comm *data, t_box	**box)
{
	t_comm	*tmp;

	*box = malloc(sizeof(t_box));
	if (!(*box))
		return (1);
	(*box)->dt_comm = data;
	(*box)->oper = NULL;
	(*box)->next = NULL;
	while (data)
	{
		if (is_logic_oper(data->oper))
		{
			if (add_new_container(&data, box))
				return (1);
			tmp = (*box)->dt_comm;
			if (move_args(&(*box)->dt_comm, &tmp))
				return (1);
		}
		else
			data = data->next;
	}
	return (0);
}
