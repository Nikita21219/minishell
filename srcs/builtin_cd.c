#include "../includes/minishell.h"

t_envr	*take_path_env(t_envr **env, char *s)
{
	t_envr	*p;

	p = *env;
	while (p)
	{
		if (is_same_lines(p->key, s))
			return (p);
		p = p->next;
	}
	return (NULL);
}

int	ft_cd_prev_dir(t_data *data, t_envr *pwd, t_envr *oldpwd, char *path)
{
	path = oldpwd->val;
	if (!is_same_lines(data->comm->args[1], "-"))
		return (printf("cd: %s: %s\n", data->comm->args[1], strerror(errno)));
	if (!path)
		return (printf("cd: OLDPWD not set\n"));
	if (chdir(path))
		return (printf("cd: %s: %s\n", data->comm->args[1], strerror(errno)));
	oldpwd->val = pwd->val;
	pwd->val = path;
	return (0);
}

int	ft_cd_with_arg(t_data *data, t_envr *pwd, t_envr *oldpwd)
{
	char	*path;

	path = data->comm->args[1];
	if (data->comm->args[1][0] == '~')
	{
		path = ft_strjoin(getenv("HOME"), (path + 1));
		if (path)
			return (printf("Error malloc cd\n"));
		if (chdir(path))
		{
			free (path);
			return (printf("cd: %s: %s\n", \
			data->comm->args[1], strerror(errno)));
		}
	}
	if (data->comm->args[1][0] == '-')
		return (ft_cd_prev_dir(data, pwd, oldpwd, path));
	if (chdir(path))
		return (printf("cd: %s: %s\n", data->comm->args[1], strerror(errno)));
	oldpwd->val = pwd->val;
	pwd->val = path;
	return (0);
}

int	ft_cd(t_data *data)
{
	t_envr	*pwd;
	t_envr	*oldpwd;

	pwd = take_path_env(&data->env, "PWD");
	oldpwd = take_path_env(&data->env, "OLDPWD");
	if (!(data->comm->args[1]))
	{
		if (chdir(getenv("HOME")))
			return (printf("cd: %s: %s\n", \
			data->comm->args[1], strerror(errno)));
		free (oldpwd->val);
		oldpwd->val = pwd->val;
		pwd->val = ft_strdup(getenv("HOME"));
		if (!pwd->val)
			return (printf("Error malloc cd\n"));
		return (0);
	}
	return (ft_cd_with_arg(data, pwd, oldpwd));
}
