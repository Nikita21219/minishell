#include "../includes/minishell.h"

void	increment_shlvl(t_data *data)
{
	t_envr	*env;
	char	*ptr_to_free;

	env = data->env;
	while (env)
	{
		if (is_same_lines(env->key, "SHLVL"))
		{
			ptr_to_free = env->val;
			env->val = ft_itoa(ft_atoi(env->val) + 1);
			free(ptr_to_free);
			break ;
		}
		env = env->next;
	}
}

void	pars_and_launch(t_data *data)
{
	t_comm	*start_dt;
	t_box	*box;

	if (parser(data) || check_tilda(&data->comm))
	{
		freedata(data);
		return ;
	}
	// tmp_print_arg_after_parser(data->comm);
	// exit(0);
	start_dt = data->comm;
	// tmp_print_arg_after_parser(data->comm);
	// exit(0);
	init_containers(data->comm, &box);
	launcher(data);
	freedata(data);
	return ;
}

void	minishell(t_data *data, char **env)
{
	int		err;

	take_start_env(data, env);
	increment_shlvl(data);
	while (1)
	{
		err = errno;
		if (!data->env)
			error_mes_with_exit("🔥mini_hell🔥: error environment\n", data);
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
		pars_and_launch(data);
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
