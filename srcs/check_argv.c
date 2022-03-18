#include "../includes/minishell.h"

int	check_argv(int argc, char **argv, char **env, t_data *data)
{
	(void) data;
	(void) env;
	if (argc != 1)
	{
		printf("mini_hell: %s: No such file or directory\n", argv[1]);
		return (1);
	}
	return (0);
}
