#include "../includes/minishell.h"

void	init_index(t_comm *dt)
{
	int	i;

	i = 0;
	while (dt)
	{
		dt->i = i++;
		dt = dt->next;
	}
}

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

void	pars_and_launch(t_data *data, int i)
{
	t_comm	*start_dt;
	t_box	*box;
	int		ch;

	ch = i;
	if (parser(data, i) || check_tilda(&data->comm))
	{
		freedata(data);
		return ;
	}
	start_dt = data->comm;
	init_containers(data->comm, &box);
	while (box)
	{
		data->comm = box->dt_comm;
		// tmp_print_arg_after_parser(data->comm);
		// exit(0);
		init_index(data->comm);
		launcher(data);
		if (set_next_box(&box))
			return ; //FIXME if fail
	}
	if (ch == 0)
		exit (errno);
	freedata(data); //FIXME check leaks and free boxes
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
		pars_and_launch(data, 1);
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
