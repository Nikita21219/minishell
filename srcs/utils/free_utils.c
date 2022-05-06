#include "../../includes/minishell.h"

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
	if (arr)
		free(arr);
	arr = NULL;
}

int	continue_with_print(char *err_str)
{
	printf("%s\n", err_str);
	return (1);
}

int	handle_error_executor(int error)
{
	if (error == PIPE_ERR)
		return (continue_with_print("Error: pipe() returned fail\n"));
	if (error == FORK_ERR)
		return (continue_with_print("Error: fork() returned fail\n"));
	if (error == DUP_ERR)
		return (continue_with_print("Error: dup2() returned fail\n"));
	if (error == CLOSE_ERR)
		return (continue_with_print("Error: close() returned fail\n"));
	if (error == EXEC_ERR)
		return (continue_with_print("Error: execve() returned fail\n"));
	if (error == MALLOC_ERR)
		return (continue_with_print("Error: malloc() returned fail\n"));
	if (error == OPEN_ERR)
		return (continue_with_print("Error: open() returned fail\n"));
	return (0);
}