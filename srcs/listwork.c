#include "../includes/minishell.h"

t_data	*addelem(t_data *data)
{
	t_data	*temp;
	t_data	*p;

	temp = (t_data *)malloc(sizeof(t_data));
	if (!temp)
		return (NULL);
	temp->args = NULL;
	temp->comm = NULL;
	temp->flags = NULL;
	temp->next = NULL;
	if (!data)
		return (temp);
	p = data;
	while (p->next)
		p = p->next;
	p->next = temp;
	return (temp);
}
