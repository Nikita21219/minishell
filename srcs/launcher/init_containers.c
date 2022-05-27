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
	new->next = NULL;
	p->next = new;
	return (0);
}

int	init_containers(t_comm *data, t_box	**box)
{
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
		}
		else
			data = data->next;
	}
	return (0);
}
