#include "../../includes/minishell.h"

int	ft_echo(t_comm com)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (is_same_lines(com.args[++i], "-n"))
		a++;
	while (com.args[i])
	{
		printf("%s", com.args[i++]);
		if (com.args[i])
			printf(" ");
	}
	if (a == 0)
		printf("\n");
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
	if (data->comm->args[1] && data->comm->args[2])
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
	{
		errno = ft_atoi(data->comm->args[1]);
		printf("exit\n");
	}
	freedata(data);
	delenv(&data->env);
	exit(errno);
}
