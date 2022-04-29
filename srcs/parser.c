#include "../includes/minishell.h"

int	vars_quote_check(char **str, char **s, int i, t_comm *data)
{
	char	quote;

	if ((*s)[i] == '$')
	{
		if (write_arg(str, s, i))
			return (-1);
		return (takevar(s, str, data));
	}
	if ((*s)[i] == 34 || (*s)[i] == 39)
	{
		quote = (*s)[i];
		if (check_second_qoute(*s, i, quote))
		{
			if (write_arg(str, s, i))
				return (-1);
			(*s)++;
			i = check_quote(s, str, quote, data);
			if (i < 0)
				return (-1);
			i = -1;
			(*s)++;
		}
	}
	// i = check_wildcard_arg(str, s, i, data);
	return (++i);
}

int	takecommand(t_comm *data, char **s)
{
	int		i;

	i = 0;
	while ((*s)[i] && i >= 0 && !ft_space((*s)[i]) \
		&& operand(data, s, &i, &data->comm))
		i = vars_quote_check(&data->comm, s, i, data);
	if (i < 0 || write_arg(&data->comm, s, i))
	{
		printf("Error malloc in parse\n");
		errno = 12;
		return (1);
	}
	return (0);
}

int	takeargs(t_comm *data, char **s)
{
	int	i;
	int	a;

	a = 1;
	data->args[a] = NULL;
	while ((*s)[0] && !data->oper)
	{
		i = 0;
		while ((*s)[i] && i >= 0 && !ft_space((*s)[i]) \
			&& operand(data, s, &i, &data->args[a]))
			i = vars_quote_check(&data->args[a], s, i, data);
		if (i < 0 || write_arg(&data->args[a], s, i))
		{
			if (i != -2)
				printf("Error malloc in parse\n");
			return (1);
		}
		while ((**s) && ft_space(**s))
			(*s)++;
		while (data->args[a])
			a++;
		if (take_arg_mass(&data->args, a))
			return (1);
	}
	return (0);
}

int	checkallcommands(t_comm *p)
{
	while (p)
	{
		if ((!p->comm && !(is_same_lines(p->oper, ">") || \
		is_same_lines(p->oper, ">>") || is_same_lines(p->oper, "<") \
		|| is_same_lines(p->oper, "<<"))) || (p->oper && !p->next))
		{
			printf("Parse error\n");
			errno = 22;
			return (1);
		}
		p = p->next;
	}
	return (0);
}

int	parser(t_data *data)
{
	t_comm	*p;
	char	*str;

	str = data->instr;
	while (*str)
	{
		while (*str && ft_space(*str))
			str++;
		if (!(*str))
			break ;
		p = addelem(data);
		if (!p)
		{
			printf("Error malloc in parse\n");
			errno = 12;
			return (1);
		}
		if (takecommand(p, &str))
			return (1);
		while (*str && ft_space(*str))
			str++;
		if (takeargs(p, &str))
			return (1);
	}
	return (checkallcommands(data->comm));
}
