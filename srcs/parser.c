#include "../includes/minishell.h"

int	vars_quote_check(char **str, char **s, int i, t_comm *data)
{
	char	quote;

	if ((*s)[i] == '$')
	{
		if (write_arg(str, s, i))
			error_mes_with_exit("Error malloc\n", data->data);
		return (takevar(s, str, data));
	}
	if ((*s)[i] == 34 || (*s)[i] == 39)
	{
		quote = (*s)[i];
		if (check_second_qoute(*s, i, quote))
		{
			i = write_arg(str, s, i);
			if (i)
				error_mes_with_exit("Error malloc in parse\n", data->data);
			(*s)++;
			i = check_quote(s, str, quote, data);
			i = -1;
			(*s)++;
		}
	}
	return (++i);
}

void	takecommand(t_comm *data, char **s)
{
	int		i;

	i = 0;
	while ((*s)[i] && !ft_space((*s)[i]) && operand(data, s, i))
		i = vars_quote_check(&data->comm, s, i, data);
	if (write_arg(&data->comm, s, i))
		error_mes_with_exit("Error malloc in parse\n", data->data);
}

void	takeargs(t_comm *data, char **s)
{
	int	i;
	int	a;

	a = 1;
	data->args[a] = NULL;
	i = 0;
	while ((*s)[i] && operand(data, s, i))
	{
		while ((*s)[i] && !ft_space((*s)[i]) && operand(data, s, i))
			i = vars_quote_check(&data->args[a], s, i, data);
		if (write_arg(&data->args[a], s, i))
			error_mes_with_exit("Error malloc in parse\n", data->data);
		while ((**s) && ft_space(**s))
			(*s)++;
		a++;
		data->args[a] = NULL;
		i = 0;
	}
	if (data->oper)
		(*s)++;
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
			error_mes_with_exit("Error malloc in parse\n", data);
		takecommand(p, &str);
		while (*str && ft_space(*str))
			str++;
		takeargs(p, &str);
	}
	p = data->comm;
	while (p)
	{
		if (!p->comm || (p->oper && !p->next))
		{
			printf("Parse error\n");
			return (0);
		}
		else
			p = p->next;
	}
	return (1);
}
