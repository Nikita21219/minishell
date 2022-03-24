#include "../includes/minishell.h"

// void	writepartstr(char **s, t_data *data, int i)

// void	check_dquote(char **s, t_data *data, char quote, int i)
// {
// 	char	*tmp1;
// 	char	*tmp2;

// 	tmp1 = data->args;
// 	while ((*s)[i] != quote)
// 		i++;
// 	if (!tmp1)
// 		data->args = ft_substr(*s, 0, i++);
// 	else
// 	{
// 		tmp2 = ft_substr(*s, 0, i++);
// 		data->args = ft_strjoin(tmp1, tmp2);
// 		free(tmp1);
// 		free(tmp2);
// 	}
// 	while (i--)
// 		(*s)++;
// }

int	check_quote(char **s, t_data *data, char quote)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	if (quote == 34)
	{
		check_dquote(s, data, quote, i);
		return (-1);
	}
	tmp1 = data->args;
	while ((*s)[i] != quote)
		i++;
	if (!tmp1)
		data->args = ft_substr(*s, 0, i++);
	else
	{
		tmp2 = ft_substr(*s, 0, i++);
		data->args = ft_strjoin(tmp1, tmp2);
		free(tmp1);
		free(tmp2);
	}
	while (i--)
		(*s)++;
	return (i);
}

int	write_arg(t_data *data, char **s, int i)
{
	char	*tmp1;
	char	*tmp2;

	if (i > 0 && (*s)[i])
	{
		if (!data->args)
			data->args = ft_substr(*s, 0, i);
		else
		{
			tmp1 = data->args;
			tmp2 = ft_substr(*s, 0, i);
			data->args = ft_strjoin(tmp1, tmp2);
			free(tmp1);
			free(tmp2);
		}
		while (i--)
			(*s)++;
		if ((**s) == '|')
			(*s)++;
	}
	return (i);
}

int	check_second_qoute(char *s, int i, char quote)
{
	while (s[++i])
		if (s[i] == quote)
			return (1);
	return (0);
}
