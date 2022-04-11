#include "../includes/minishell.h"

char	*heredoc(t_comm *data)
{
	char	*line;
	char	*ptr_to_free;
	char	*result;
	char	*line_with_nl;

	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (NULL);
	line = ft_calloc(1, sizeof(char));
	if (!line)
		return (NULL);
	while (1)
	{
		free(line);
		line = readline("> ");
		if (!line)
			return (NULL);
		if (is_same_lines(data->next->comm, line))
			break ;
		line_with_nl = ft_strjoin(line, "\n");
		if (!line_with_nl)
		{
			free(line);
			free(result);
			return (NULL);
		}
		ptr_to_free = result;
		result = ft_strjoin(result, line_with_nl);
		free(line_with_nl);
		free(ptr_to_free);
		if (!result)
		{
			free(line);
			free(ptr_to_free);
			return (NULL);
		}
	}
	free(line);
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
	{
		printf("ERROR from dup2 in heredoc");
		exit(0);
	}
	if (close_fd(data))
	{
		printf("ERROR from close in heredoc");
		exit(0);
	}
	printf("%s", result);
	return (result);
}

char	*implement_redirections(t_comm *data)
{
	if (is_same_lines(data->oper, "<<"))
	{
		heredoc(data);
	}
	return (NULL);
}
