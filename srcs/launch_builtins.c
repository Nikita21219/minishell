#include "../includes/minishell.h"

int	is_builtins(char *comm)
{
	if (is_same_lines(comm, "echo"))
		return (BUILTIN_ECHO);
	if (is_same_lines(comm, "cd"))
		return (BUILTIN_CD);
	if (is_same_lines(comm, "pwd"))
		return (BUILTIN_PWD);
	if (is_same_lines(comm, "export"))
		return (BUILTIN_EXPORT);
	if (is_same_lines(comm, "unset"))
		return (BUILTIN_UNSET);
	if (is_same_lines(comm, "env"))
		return (BUILTIN_ENV);
	if (is_same_lines(comm, "exit"))
		return (BUILTIN_EXIT);
	return (0);
}

int	launch_builtins(t_comm *data)
{
	int	builtin;

	builtin = is_builtins(data->comm);
	if (builtin == BUILTIN_ECHO)
		return (ft_echo(*data));
	if (builtin == BUILTIN_PWD)
		return (ft_pwd());
	printf("mini_hell: %s: command not found\n", data->comm);
	return (0);
}
