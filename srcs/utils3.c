#include "../includes/minishell.h"

char	*get_path_to_comm(char	**comm_split)
{
	int     i;
	char    *path_to_comm;
	char    *ptr_to_free;

	i = -1;
	while (comm_split[++i])
	{
		ptr_to_free = comm_split[i];
		comm_split[i] = ft_strjoin("/", comm_split[i]);
		free(ptr_to_free);
		if (!comm_split[i])
			return (NULL);
	}
	i = -1;
	path_to_comm = ft_calloc(1, sizeof(char));
	if (!path_to_comm)
		return (NULL);
	while (comm_split[++i])
	{
		free(path_to_comm);
		path_to_comm = ft_strjoin(path_to_comm, comm_split[i]);
		if (!path_to_comm)
			return (NULL);
	}
	return (path_to_comm);
}

int	create_pipe(t_comm *data)
{
	if (pipe(data->fd) == -1)
		return (1);
	return (0);
}

int	is_redirect(char *op)
{
	if (is_same_lines(op, "<<"))
		return (1);
	if (is_same_lines(op, ">>"))
		return (1);
	if (is_same_lines(op, "<"))
		return (1);
	if (is_same_lines(op, ">"))
		return (1);
	return (0);
}

int	duplicate_fd(t_comm *data, int idx, int count_comm)
{
	if (idx == 0)
	{
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			return (1);
	}
	else if (idx + 1 == count_comm)
	{
		if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
			return (1);
	}
	else
	{
		if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
			return (1);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			return (1);
	}
	return (0);
}
