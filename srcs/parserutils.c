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
	if (a > 0)
	{
		while (--a)
			(*s)++;
		return (0);
	}
	return (1);
}

int	check_quote(char **s, char **str, char quote, t_comm *data)
{
	int		i;

	i = 0;
	while ((*s)[i] && (*s)[i] != quote)
	{
		if (quote == 34 && (*s)[i] == '$')
		{
			if (write_arg(str, s, i))
				return (-1);
			i = takevar(s, str, data);
			if (i < 0)
				return (-1);
		}
		else
			i++;
	}
	if (write_arg(str, s, i))
		return (-1);
	return (i);
}

int	write_arg(char **arg, char **s, int i)
{
	char	*tmp1;
	char	*tmp2;

	if (i == 0)
		return (0);
	if (!ft_strlen(*arg))
		*arg = ft_substr(*s, 0, i);
	else
	{
		tmp1 = *arg;
		tmp2 = ft_substr(*s, 0, i);
		if (!tmp2)
			return (1);
		*arg = ft_strjoin(tmp1, tmp2);
		free(tmp1);
		free(tmp2);
	}
	if (!(*arg))
	{
		errno = 12;
		return (1);
	}
	while (i--)
		(*s)++;
	return (0);
}

int	check_second_qoute(char *s, int i, char quote)
{
	while (s[++i])
		if (s[i] == quote)
			return (1);
	return (0);
}

t_envr	*search_var(char *tmp, t_envr *p, t_envr *vars)
{
	while (p && !is_same_lines(tmp, p->key))
		p = p->next;
	if (!p && vars)
	{
		p = vars;
		while (p && !is_same_lines(tmp, p->key))
			p = p->next;
	}
	return (p);
}
