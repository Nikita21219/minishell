#include "../includes/minishell.h"

void	free_arrs(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
	}
	free(arr);
}

int	continue_with_print(char *err_str)
{
	printf("%s\n", err_str);
	return (1);
}

int	handle_error_executor(int error)
{
	if (error == -1)
		return (continue_with_print("Error: pipe() returned fail\n"));
	if (error == -2)
		return (continue_with_print("Error: fork() returned fail\n"));
	if (error == -3)
		return (continue_with_print("Error: dup2() returned fail\n"));
	if (error == -4)
		return (continue_with_print("Error: close() returned fail\n"));
	if (error == -5)
		return (continue_with_print("Error: execve() returned fail\n"));
	if (error == -6)
		return (continue_with_print("Error: dup2() or close() returned fail\n")); //FIXME to replace text - only one error, without 'or'
	return (0);
}
