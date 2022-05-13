#include "../../includes/minishell.h"

int	is_logic_oper(char *str)
{
	if (is_same_lines("&&", str))
		return (1);
	if (is_same_lines("||", str))
		return (2);
	return (0);
}

int	count_command(t_comm *data)
{
	int	res;

	res = 0;
	while (data)
	{
		res++;
		data = data->next;
	}
	return (res);
}

t_comm	*get_copy_dt(t_comm *data)
{
	t_comm	*res;

	res = malloc(sizeof(t_comm));
	// printf("res adress = %p\n", res);
	if (res == NULL)
		return (NULL);
	res->args = data->args;
	res->comm = data->comm;
	res->data = data->data;
	res->fd[0] = data->fd[0];
	res->fd[1] = data->fd[1];
	res->i = data->i;
	res->next = data->next;
	res->oper = data->oper;
	res->prev = data->prev;
	res->status = data->status;
	return (res);
}

int	add_new_container(t_comm *data, t_box **box)
{
	t_box	*new;
	t_comm	*copy_dt;

	new = malloc(sizeof(t_box));
	if (new == NULL)
		return (1);
	copy_dt = get_copy_dt(data->next); //FIXME if returned fail
	if (copy_dt == NULL)
		return (1);
	new->dt_comm = copy_dt;
	data->next = NULL;
	(*box)->next = new;
	*box = (*box)->next;
	return (0);
}

int	init_containers(t_comm *data, t_box	**box)
{
	t_box	*tmp_box;

	(*box)->dt_comm = get_copy_dt(data);
	tmp_box = *box;
	while (data)
	{
		if (is_logic_oper(data->oper))
			if (add_new_container(data, &tmp_box))
				continue ; //FIXME if add_new_container returned fail, need to free sctruct
		data = data->next;
	}
	tmp_box->next = NULL;
	return (0);
}
