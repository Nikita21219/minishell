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

int	takevar(char **s, char **str, t_comm *data)
{
	char	*tmp;
	t_envr	*p;
	int		i;

	i = 0;
	p = data->data->env;
	(*s)++;
	if (ft_isdigit(**s))
	{
		while ((**s) && ft_isdigit(**s))
			(*s)++;
		return (0);
	}
	while ((*s)[i] && ((*s)[i] == '_' || ft_isalnum((*s)[i])))
		i++;
	tmp = ft_substr(*s, 0, i);
	if (!tmp)
		error_mes_with_exit("Error malloc\n", data->data);
	while (p && !is_same_lines(tmp, p->key))
		p = p->next;
	if (p)
	{
		if (*str)
		{
			free(tmp);
			tmp = (*str);
			*str = ft_strjoin(tmp, p->val);
		}
		else
			*str = ft_strdup(p->val);
		if (!(*str))
			error_mes_with_exit("Error malloc\n", data->data);
	}
	while (i--)
		(*s)++;
	free(tmp);
	return (0);
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
				error_mes_with_exit("Error malloc\n", data->data);
			i = takevar(s, str, data);
		}
		else
			i++;
	}
	if (write_arg(str, s, i))
		error_mes_with_exit("Error malloc\n", data->data);
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
		return (1);
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
