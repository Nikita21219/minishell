#include "../includes/minishell.h"

int	create_pipes(t_comm *data)
{
	int	i;

	i = 0;
	while (data->next)
	{
		if (pipe(data->fd) == -1)
			return (1);
		data = data->next;
	}
	return (0);
}

void	add_ptr_prev_to_data(t_comm *data)
{
	int i;

	i = 0;
	data->prev = NULL;
	while (data->next)
	{
		data->i = i++;
		data->next->prev = data;
		data = data->next;
	}
	data->i = i;
}

void	close_fd(t_comm *data)
{
	while (data->prev)
		data = data->prev;
	while (data->next)
	{
		// printf("command = %s\n", data->comm);
		if (data->fd[0] && data->fd[1])
		{
			if (close(data->fd[0]) == -1)
			{
				printf("FAIL close 1 errno=%d\n", errno);
				exit(1); //FIXME
			}
			if (close(data->fd[1]) == -1)
			{
				printf("FAIL close 2 errno=%d\n", errno);
				exit(1); //FIXME
			}
		}
		data = data->next;
	}
}
