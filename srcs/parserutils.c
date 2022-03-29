#include "../includes/minishell.h"

int	operand(t_comm	*data, char **s, int i)
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
	if (a > 0 && !data->oper)
		error_mes_with_exit("Error malloc\n", data->data);
	if (a > 0)
		return (0);
	return (1);
}

int	takevar(char **s, char **str, int i, t_comm *data)
{
	char	*tmp1;
	char	*tmp2;
	t_envr	*p;

	if (write_arg(str, s, i, 0) == -100)
		error_mes_with_exit("Error malloc\n", data->data);
	i = 0;
	p = data->data->env;
	tmp1 = *str;
	while ((*s)[i] && (*s)[i] != ' ' && (*s)[i] != 34 && operand(data, s, i))
		i++;
	tmp2 = ft_substr(*s, 1, i - 1);
	if (!tmp2)
		error_mes_with_exit("Error malloc\n", data->data);
	while (p && !is_same_lines(tmp2, p->key))
		p = p->next;
	while ((**s) && (**s) != ' ' && operand(data, s, i))
		(*s)++;
	if (p && is_same_lines(tmp2, p->key))
	{
		*str = ft_strjoin(tmp1, p->val);
		free(tmp1);
		if (!(*str))
			error_mes_with_exit("Error malloc\n", data->data);
	}
	free(tmp2);
	return (-1);
}

int	check_quote(char **s, char **str, char quote, t_comm *data)
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
	if (i == -100)
		error_mes_with_exit("Error malloc\n", data->data);
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
		if (!tmp2)
			return (-100);
		free(tmp2);
		if (!(*arg))
			return (-100);
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
