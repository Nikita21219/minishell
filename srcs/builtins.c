#include "../includes/minishell.h"

int	ft_echo(t_comm com)
{
	int	i;

	i = 1;
	if (is_same_lines(com.args[i], "-n"))
	{
		while (com.args[++i])
		{
			printf("%s", com.args[i]);
			if (com.args[i + 1])
				printf(" ");
		}
	}
	else
	{
		while (com.args[i])
		{
			printf("%s", com.args[i++]);
			if (com.args[i])
				printf(" ");
		}
		printf("\n");
	}
	return (0);
}

int	ft_pwd(t_envr *env)
{
	t_envr	*p;

	p = env;
	while (p)
	{
		if (is_same_lines(p->key, "PWD"))
		{
			printf("%s\n", p->val);
			return (0);
		}
		p = p->next;
	}
	return (1);
}

int	ft_env(t_envr *env)
{
	t_envr	*p;

	p = env;
	if (!p)
		return (1);
	while (p)
	{
		printf("%s=%s\n", p->key, p->val);
		p = p->next;
	}
	return (0);
}

int	ft_exit(t_data *data)
{
	int		i;

	i = 0;
	if (data->comm->args[2])
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	data->comm->args[1] = data->comm->args[1];
	while (data->comm->args[1][i])
	{
		if (!(data->comm->args[1][i] >= 48 && data->comm->args[1][i++] <= 57))
		{
			printf("exit: privet: numeric argument required\n");
			i = 0;
			break ;
		}
	}
	if (i != 0)
		i = ft_atoi(data->comm->args[1]);
	freedata(data);
	delenv(&data->env);
	exit (i);
}
