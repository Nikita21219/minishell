#include "../includes/minishell.h"

int	check_right_var(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(*arg))
		return (1);
	while (arg[i] && arg[i] != '=')
		if (!ft_isalnum(arg[i++]))
			return (1);
	if (!arg[i] || arg[i] != '=')
		return (1);
	return (0);
}

int	add_list_env(t_envr **env, char *arg)
{
	t_envr	*p;
	int		i;

	i = 0;
	p = malloc(sizeof(t_envr));
	if (!p)
	{
		printf("Error malloc export\n");
		return (1);
	}
	while (arg[i] != '=')
		i++;
	p->key = ft_substr(arg, 0, i++);
	p->val = ft_substr(arg, i, ft_strlen(arg));
	if (!p->key || !p->val)
	{
		printf("Error malloc export\n");
		return (1);
	}
	p->next = *env;
	*env = p;
	return (0);
}

int	ft_export(t_data *data)
{
	int		i;

	i = 1;
	while (data->comm->args[i])
	{
		if (check_right_var(data->comm->args[i]))
		{
			printf("export: '%s': not a valid identifier\n", \
			data->comm->args[i++]);
			continue ;
		}
		if (add_list_env(&data->env, data->comm->args[i++]))
			return (1);
	}
	return (0);
}
