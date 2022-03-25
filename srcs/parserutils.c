#include "../includes/minishell.h"

int	takevar(char **s, char **str, int i)
{
	char	*tmp1;
	char	*tmp2;

	write_arg(str, s, i, 0);
	i = 0;
	tmp1 = *str;
	tmp2 = getenv("PWD");
	while ((**s) && (**s) != ' ')
	{
		(*s)++;
		i++;
	}
	*str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	return (-1);
}

int	check_quote(char **s, char **str, char quote)
{
	int		i;

	i = 0;
	while ((*s)[i] && (*s)[i] != quote)
	{
		if (quote == 34 && (*s)[i] == '$')
			takevar(s, str, i);
		i++;
	}
	i = write_arg(str, s, i, quote);
	return (i);
}

int	write_arg(char **arg, char **s, int i, char quote)
{
	char	*tmp1;
	char	*tmp2;

	if (!(*arg))
		*arg = ft_substr(*s, 0, i);
	else
	{
		tmp1 = *arg;
		tmp2 = ft_substr(*s, 0, i);
		*arg = ft_strjoin(tmp1, tmp2);
		free(tmp1);
		free(tmp2);
	}
	if (quote)
		i++;
	while (i--)
		(*s)++;
	if ((**s) == '|')
		(*s)++;
	return (i);
}

int	check_second_qoute(char *s, int i, char quote)
{
	while (s[++i])
		if (s[i] == quote)
			return (1);
	return (0);
}
