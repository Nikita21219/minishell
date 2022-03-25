#include "../includes/minishell.h"

int	operand(t_data	*data, char **s, int i)
{
	int	a;

	a = 0;
	if ((*s)[i] == '<')
	{
		if ((*s)[i] == (*s)[i + 1])
			a++;
		data->oper = ft_substr(*s, i, ++a);
	}
	if ((*s)[i] == '>')
	{
		if ((*s)[i] == (*s)[i + 1])
			a++;
		data->oper = ft_substr(*s, i, ++a);
	}
	if ((*s)[i] == '|')
		data->oper = ft_substr(*s, i, ++a);
	if (a > 0)
		return (0);
	return (1);
}

int	takevar(char **s, char **str, int i, t_data *data)
{
	char	*tmp1;
	char	*tmp2;
	t_envr	*p;

	write_arg(str, s, i, 0);
	i = 0;
	p = data->envr;
	tmp1 = *str;
	while ((*s)[i] && (*s)[i] != ' ' && operand(data, s, i))
		i++;
	tmp2 = ft_substr(*s, 1, i - 1);
	while (p && !is_same_lines(tmp2, p->key))
		p = p->next;
	while ((**s) && (**s) != ' ' && operand(data, s, i))
		(*s)++;
	if (is_same_lines(tmp2, p->key))
	{
		*str = ft_strjoin(tmp1, p->val);
		free(tmp1);
	}
	free(tmp2);
	return (-1);
}

int	check_quote(char **s, char **str, char quote, t_data *data)
{
	int		i;

	i = 0;
	while ((*s)[i] && (*s)[i] != quote)
	{
		if (quote == 34 && (*s)[i] == '$')
			takevar(s, str, i, data);
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
	return (i);
}

int	check_second_qoute(char *s, int i, char quote)
{
	while (s[++i])
		if (s[i] == quote)
			return (1);
	return (0);
}
