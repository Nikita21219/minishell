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

int	get_count_comm_split(char **comm_split)
{
	int	i;
	int	count_comm;

	i = -1;
	count_comm = 0;
	if (comm_split && *comm_split)
		while (comm_split[++i])
			count_comm++;
	return (count_comm);
}

int	is_correct_comm(char *comm, char **dirs)
{
	int		i;
	int		counter;
	int		count_comm_split;
	char	**comm_split;
	char	*path_to_comm;

	i = -1;
	counter = 0;
	comm_split = ft_split(comm, '/'); //FIXME
	count_comm_split = get_count_comm_split(comm_split);
	free(comm_split[count_comm_split - 1]);
	comm_split[count_comm_split - 1] = NULL;
	path_to_comm = get_path_to_comm(comm_split); //FIXME free if not allocated
	free_arrs(comm_split);
	i = -1;
	while (dirs[++i])
	{
		if (is_same_lines(dirs[i], path_to_comm))
		{
			free(path_to_comm);
			return (1);
		}
	}
	free(path_to_comm);
	return (0);
}

// /usr/bin/grep
