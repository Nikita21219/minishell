#include "../../includes/minishell.h"

void	init_fd(t_comm *data, int *fd)
{
	if (is_same_lines(data->oper, ">"))
		*fd = open(data->next->comm, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		*fd = open(data->next->comm, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
}

int	ft_fprintf(char *str)
{
	write(2, "mini_hell: ", 11); //FIXME if returned fail
	write(2, str, ft_strlen(str)); //FIXME if returned fail
	write(2, ": No such file or directory\n", 29); //FIXME if returned fail
	return (0);
}

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
		init_fd(data, &fd);
		if (fd == -1)
			return (OPEN_ERR);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (DUP_ERR);
		if (data && data->prev && is_same_lines(data->prev->oper, "|"))
			if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
				return (DUP_ERR);
		if (data && data->prev && is_same_lines(data->prev->oper, "<"))
			if (dup2(data->prev->fd[0], STDIN_FILENO) == -1)
				return (DUP_ERR);
		if (data && data->next && is_same_lines(data->next->oper, "<"))
			redirect_in(data->next);
		data = data->next;
	}
	if (close(fd) == -1)
		return (CLOSE_ERR);
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
	if (data && data->prev && is_same_lines(data->prev->oper, ">"))
	{
		// fprintf(stderr, "test\n"); // FIXME fprintf is not allow
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			return (DUP_ERR);
	}
	return (0);
}

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
