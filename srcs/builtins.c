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
	if (!p || !take_path_env(&env, "PATH"))
	{
		printf("env: No such file or directory\n");
		return (1);
	}
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
	while (data->comm->args[1] && data->comm->args[1][i])
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
	exit(i);
}

void	ft_unset(t_comm	*comm)
{
	t_envr	*p1;
	t_envr	*p2;
	int		i;

	i = 1;
	while (comm->args[i])
	{
		p1 = comm->data->env;
		p2 = take_path_env(&comm->data->env, comm->args[i]);
		if (!p2)
		{
			i++;
			continue ;
		}
		if (is_same_lines(p1->key, comm->args[i++]))
		{
			comm->data->env = comm->data->env->next;
			free (p1);
			continue ;
		}
		while (p1->next != p2)
			p1 = p1->next;
		if (p2->next == NULL)
		{
			free(p2);
			p1->next = NULL;
		}
		else
		{
			p1->next = p2->next;
			free(p2);
		}
	}
}
