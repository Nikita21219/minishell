#include "../includes/minishell.h"

int	is_builtins_in_main_proc(char *comm)
{
	if (is_same_lines(comm, "cd"))
		return (BUILTIN_CD);
	if (is_same_lines(comm, "exit"))
		return (BUILTIN_EXIT);
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
	if (is_same_lines(comm, "echo"))
		return (BUILTIN_ECHO);
	if (is_same_lines(comm, "pwd"))
		return (BUILTIN_PWD);
	if (is_same_lines(comm, "export"))
		return (BUILTIN_EXPORT);
	if (is_same_lines(comm, "unset"))
		return (BUILTIN_UNSET);
	return (0);
}

int	launch_builtins(t_data *data)
{
	int	builtin;

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
	printf("mini_hell: %s: command not found\n", data->comm->comm);
	return (0);
}