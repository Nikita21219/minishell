#include "../includes/minishell.h"

int	kill_childs(t_comm *data)
{
	while (data->prev)
		data = data->prev;
	while (data)
	{
		if (kill(data->pid, SIGKILL))
			return (1);
		data = data->next;
	}
	return (0);
}