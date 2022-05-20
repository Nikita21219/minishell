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
		printf("data args %d: %s\n", j, data->args[j]);
		printf("oper: %s\n", data->oper);
		printf("i: %d\n", data->i);
		printf("\n\n");
		i++;
		data = data->next;
	}
} //FIXME delete this func

void    tmp_print_env(t_envr *env)
{
	t_envr  *envr;
	envr = env;
	while (envr)
	{
		printf("%s=%s\n", envr->key, envr->val);
        envr = envr->next;
	}
} //FIXME delete this func

void	minishell(t_data *data, char **env)
{
	int		err;

	take_start_env(data, env);
	while (1)
	{
		err = errno;
		if (!data->env)
			error_mes_with_exit("Error environment\n", data);
		data->instr = readline("🔥mini_hell🔥$ ");
		errno = err;
		if (!data->instr)
			error_mes_with_exit("\b\bexit\n", data);
		if (data->instr[0] == 0)
		{
			free(data->instr);
			continue ;
		}
		add_history(data->instr);
		if (parser(data) || check_tilda(&data->comm))
		{
			freedata(data);
			continue ;
		}
		tmp_print_arg_after_parser(data->comm);
		// exit(0);
		// tmp_print_env(data->vars);
		// exit(0);
		// add_ptr_prev_to_data(data->comm);
		launcher(data);
		freedata(data);
	}
	delenv(&data->env);
	freedata(data);
}

void	ft_takesig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_data				data;

	if (check_argv(argc, argv, env, &data))
		return (1);
	// signal(SIGINT, ft_takesig);
	// signal(SIGQUIT, SIG_IGN);
	minishell(&data, env);
	return (0);
}


