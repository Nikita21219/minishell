#include "../includes/minishell.h"

int	heredoc(t_comm *data)
{
	char	*line;
	char	*ptr_to_free;
	char	*result;
	char	*line_with_nl;

	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (1);
	line = ft_calloc(1, sizeof(char));
	if (!line)
		return (1);
	while (1)
	{
		free(line);
		line = readline("> ");
		if (!line)
			return (1);
		if (is_same_lines(data->next->comm, line))
			break ;
		line_with_nl = ft_strjoin(line, "\n");
		if (!line_with_nl)
		{
			free(line);
			free(result);
			return (1);
		}
		ptr_to_free = result;
		result = ft_strjoin(result, line_with_nl);
		free(line_with_nl);
		free(ptr_to_free);
		if (!result)
		{
			free(line);
			free(ptr_to_free);
			return (1);
		}
	}
	free(line);
	write(data->fd[1], result, ft_strlen(result));
	return (0);
}

int	duplicate_fd_for_heredoc(t_comm *data)
{
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		return (DUP_ERR);
	return (0);
}
