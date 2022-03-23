#include "../includes/minishell.h"

void	minishell(t_data *data)
{
	char	*str;
	int		i;

	while (1)
	{
		i = 0;
		str = readline(READLINE_RED "mini_hell$ " TERM_RESET);
		if (!str)
			return ;
		parser(data, str);
		add_history(str);
		free(str);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = NULL;
	if (check_argv(argc, argv, env, data))
		return (1);
	minishell(data);
	return (0);
}
