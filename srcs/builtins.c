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

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		return (1);
	return (0);
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
	while (data->comm->args[1][i])
	{
		if (!(data->comm->args[1][i] >= 48 && data->comm->args[1][i++] <= 57))
		{
			printf("exit: %s: numeric argument required\n", data->comm->args[1]);
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

int	ft_cd(t_comm *comm)
{
	if (chdir(comm->args[1]))
		return (printf("cd: %s: %s\n", comm->args[1], strerror(errno)));
	return (0);
}
