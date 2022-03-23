#include "../includes/minishell.h"

int	check_quote(char **s, t_data *data, char quote)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
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
	}
	return (i);
}
