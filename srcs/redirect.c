#include "../includes/minishell.h"

int	redirect_out(t_comm *data)
{
	int	fd;

	fd = 0;
	while (data && (is_same_lines(data->oper, ">") \
	|| is_same_lines(data->oper, ">>")))
	{
		if (fd)
			if (close(fd) == -1)
				return (CLOSE_ERR);
		if (is_same_lines(data->oper, ">"))
			fd = open(data->next->comm, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		else
			fd = open(data->next->comm, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (fd == -1)
			return (OPEN_ERR);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (DUP_ERR);
		if (data && data->prev && is_same_lines(data->prev->oper, "|"))
			if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
				return (DUP_ERR);
		data = data->next;
	}
	return (0);
}

int	redirect_in(t_comm *data)
{
	int	fd;

	fd = 0;
	while (data && is_same_lines(data->oper, "<"))
	{
		if (fd)
			if (close(fd) == -1)
				return (CLOSE_ERR);
		fd = open(data->next->comm, O_RDONLY);
		data = data->next;
	}
	data = data->next;
	if (fd == -1)
		return (OPEN_ERR);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (DUP_ERR);
	if (data && data->next && is_same_lines(data->next->oper, "|"))
	{
		if (dup2(data->next->fd[1], STDOUT_FILENO) == -1)
			return (DUP_ERR);
	}
	else if (is_same_lines(data->prev->oper, ">"))
	{
		fprintf(stderr, "TEST data->comm: %s\n", data->prev->next->comm);
		redirect_out(data->prev);
	}
	return (0);
}

// void	*free_env_and_return_null()
// {

// }

int	count_dict(t_envr *dt_env)
{
	int	i;

	i = 0;
	while (dt_env)
	{
		i++;
		dt_env = dt_env->next;
	}
	return (i + 1);
}

char	**get_env(t_envr *dt_env)
{
	int		i;
	char	**env;
	char	*key_with_equel;
	char	*pair;

	i = 0;
	env = malloc(sizeof(char *) * count_dict(dt_env)); //FIXME check if not allocated
	while (dt_env)
	{
		key_with_equel = ft_strjoin(dt_env->key, "=");
		if (key_with_equel == NULL)
		{
			free_arrs(env);
			return (NULL);
		}
		pair = ft_strjoin(key_with_equel, dt_env->val);
		if (pair == NULL)
		{
			free_arrs(env);
			free(key_with_equel);
			return (NULL);
		}
		free(key_with_equel);
		env[i++] = pair;
		dt_env = dt_env->next;
	}
	env[i] = NULL;
	return (env);
}
