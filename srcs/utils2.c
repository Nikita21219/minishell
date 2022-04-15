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
	int	i;

	if (!data)
		return ;
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

int	close_fd(t_comm *data)
{
	while (data->prev)
		data = data->prev;
	while (data->next)
	{
		if (data->fd[0] && data->fd[1])
		{
			if (close(data->fd[0]) == -1)
				return (1);
			if (close(data->fd[1]) == -1)
				return (1);
		}
		data = data->next;
	}
	return (0);
}

int	is_correct_comm(char *comm)
{
	if (!access(comm, 1))
		return (1);
	return (0);
}

int	is_correct_path(char *comm)
{
	DIR	*dir;

	dir = opendir(comm);
	if (dir)
		return (closedir(dir));
	return (1);
}
