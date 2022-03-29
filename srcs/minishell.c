#include "../includes/minishell.h"

void	minishell(t_data *data, char **env)
{
	take_start_env(data, env);
	while (1)
	{
		if (!data->env)
			error_mes_with_exit("Error environment\n", data);
		data->instr = readline(READLINE_RED "mini_hell$ " TERM_RESET);
		if (!data->instr)
			return ;
		parser(data);
		add_history(data->instr);
		freedata(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (check_argv(argc, argv, env, &data))
		return (1);
	minishell(&data, env);
	return (0);
}
