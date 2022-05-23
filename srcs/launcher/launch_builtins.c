#include "../../includes/minishell.h"

int	is_builtins_in_main_proc(char *comm)
{
	if (is_same_lines(comm, "cd"))
		return (BUILTIN_CD);
	if (is_same_lines(comm, "exit"))
		return (BUILTIN_EXIT);
	if (is_same_lines(comm, "unset"))
		return (BUILTIN_UNSET);
	return (0);
}

int	is_builtins(char *comm)
{
	int	builtin;

	builtin = is_builtins_in_main_proc(comm);
	if (builtin)
		return (builtin);
	if (is_same_lines(comm, "env"))
		return (BUILTIN_ENV);
	if (is_same_lines(comm, "export"))
		return (BUILTIN_EXPORT);
	if (is_same_lines(comm, "echo"))
		return (BUILTIN_ECHO);
	if (is_same_lines(comm, "pwd"))
		return (BUILTIN_PWD);
	return (0);
}

int	launch_builtins(t_data *data)
{
	int		builtin;
	int		i;
	char	**env;

	builtin = is_builtins(data->comm->comm);
	if (builtin == BUILTIN_ECHO)
		return (ft_echo(*(data->comm)));
	if (builtin == BUILTIN_PWD)
		return (ft_pwd());
	if (builtin == BUILTIN_ENV)
		return (ft_env(data->env));
	if (builtin == BUILTIN_EXIT)
		return (ft_exit(data));
	if (builtin == BUILTIN_CD)
		return (ft_cd(data));
	if (builtin == BUILTIN_EXPORT)
	{
		ft_export(data);
		env = get_env(data->env);
		i = -1;
		while (env[++i])
		{
			write(data->comm->fd[1], env[i], ft_strlen(env[i]));
			write(data->comm->fd[1], "\n", 1);
		}
		return (0);
	}
	if (builtin == BUILTIN_UNSET)
	{
		ft_unset(data);
		return (0);
	}
	errno = 127;
	fprintf(stderr, "mini_hell: %s: command not found\n", data->comm->comm); // FIXME fprintf is not allow
	// perror(data->comm->comm);
	return (127);
}

int	init_var(t_comm **tmp_dt, t_data *dt, int *wait_c, int *count_comm)
{
	*tmp_dt = dt->comm;
	*wait_c = 0;
	*count_comm = get_count_comm(dt->comm);
	if (*count_comm == 0)
		return (1);
	return (0);
}
