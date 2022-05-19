#include "../../includes/minishell.h"

int	ft_echo(t_comm com)
{
	int	i;
	int	x;
	int	a;

	i = 1;
	a = 0;
	x = 0;
	while (com.args[i] && com.args[i][0] == '-' && com.args[i][1] == 'n')
	{
		while (com.args[i][++x])
			if (com.args[i][x] != 'n')
				break ;
		i++;
		a++;
	}
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
