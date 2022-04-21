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
	int TMP_TEST = 2;
	take_start_env(data, env);
	while (TMP_TEST)
	{
		if (!data->env)
			error_mes_with_exit("Error environment\n", data);
		data->instr = readline(READLINE_RED "mini_hell$ " TERM_RESET);
		if (!data->instr)
			break ;
		if (data->instr[0] == 0)
			continue ;
		add_history(data->instr);
		if (parser(data))
		{
			freedata(data);
			continue ;
		}
		// tmp_print_arg_after_parser(data->comm);
		// exit(0);
		add_ptr_prev_to_data(data->comm);
		launcher(data, env);
		freedata(data);
		// sleep(10);
	}
	delenv(&data->env);
	freedata(data);
}

void	ft_takesig(int signum)
{
	if (signum == SIGINT)
		write(1, "\nminishell: ", 13);
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_data				data;
	struct sigaction	sig;

	if (check_argv(argc, argv, env, &data))
		return (1);
	sig.sa_handler = &ft_takesig;
	sig.sa_flags = SA_USERSPACE_MASK;
	// if (sigaction(SIGINT, &sig, NULL) < 0)
	// 	perror("Minishell: Sigactoin");
	// if (sigaction(SIGQUIT, &sig, NULL) < 0)
	// 	perror("Minishell: Sigactoin");
	minishell(&data, env);
	return (0);
}
