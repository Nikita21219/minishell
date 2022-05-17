#include "../../includes/minishell.h"

int	init_result_and_line(char **line, char **result)
{
	*result = ft_calloc(1, sizeof(char));
	if (*result == NULL)
		return (1);
	*line = ft_calloc(1, sizeof(char));
	if (*line == NULL)
		return (1);
	return (0);
}

int	readline_and_free(char **line)
{
	free(*line);
	*line = readline("> ");
	if (*line == NULL)
		return (1);
	return (0);
}

int	init_line_with_nl(char **line_with_nl, char **line, char **result)
{
	*line_with_nl = ft_strjoin(*line, "\n");
	if (*line_with_nl == NULL)
	{
		free(*line);
		free(*result);
		return (1);
	}
	return (0);
}

int	heredoc(t_comm *data)
{
	char	*line;
	char	*ptr_to_free;
	char	*result;
	char	*line_with_nl;

	if (init_result_and_line(&result, &line))
		return (1);
	if (data->fd[1])
		close(data->fd[1]);
	data->fd[1] = open(".tmp_heredoc", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (data->fd[1] == -1)
	{
		fprintf(stderr, "ERROR in open func\n");
		return (OPEN_ERR);
	}
	while (1)
	{
		if (readline_and_free(&line))
			return (1);
		if (is_same_lines(data->next->comm, line))
			break ;
		if (init_line_with_nl(&line_with_nl, &line, &result))
			return (1);
		if (init_result(\
		&ptr_to_free, &line_with_nl, &line, &result))
			return (1);
	}
	free(line);
	// if (!(data->next && is_same_lines(data->next->oper, "<<")) && \
	// !(data->next && data->next->next && is_same_lines(data->next->oper, "|") && \
	// is_same_lines(data->next->next->oper, "<<")))
	// {
		// fprintf(stderr, "data->fd[1] = %d\n", data->fd[1]);
	write(data->fd[1], result, ft_strlen(result));
	// fprintf(stderr, "command number %d; fd[1] = %d\n", data->i + 1, data->fd[1]);
	// }
	free(result);
	return (0);
}

int	duplicate_fd_for_heredoc(t_comm *data)
{
	while (data && data->next && is_same_lines(data->next->oper, "<<"))
	{
	// fprintf(stderr, "TEST 2\n");
		close(data->fd[1]);
		data = data->next;
	}
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		return (DUP_ERR);
	return (0);
}
