#include "../includes/minishell.h"

void	tmp_print_arg_after_parser(t_comm *data)
{
	int j;

	int i = 0;
	int cout_comm = get_count_comm(data);
	while (i < cout_comm)
	{
		j = -1;
		printf("command: %s\n", data->comm);
		while (data->args[++j])
			printf("data args %d: %s\n", j, data->args[j]);
		printf("oper: %s\n", data->oper);
		printf("\n\n");
		i++;
		data = data->next;
	}
}

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
		add_history(data->instr);
		if (parser(data))
			continue ;
		add_ptr_prev_to_data(data->comm);
		launcher(data->comm, env);
		freedata(data);
	}
	freedata(data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (check_argv(argc, argv, env, &data))
		return (1);
	minishell(&data, env);

	return (0);
}

// cat test.txt | grep developer | wc
