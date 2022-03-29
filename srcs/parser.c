#include "../includes/minishell.h"

int	vars_quote_check(char **str, char **s, int i, t_comm *data)
{
	char	quote;

	if ((*s)[i] == '$')
		i = takevar(s, str, i, data);
	if ((*s)[i] == 34 || (*s)[i] == 39)
	{
		quote = (*s)[i];
		if (check_second_qoute(*s, i, quote))
		{
			i = write_arg(str, s, i, 0);
			if (i == -100)
				error_mes_with_exit("Error malloc\n", data->data);
			(*s)++;
			i = check_quote(s, str, quote, data);
		}
	}
	return (i);
}

void	takecommand(t_comm *data, char **s)
{
	int		i;

	i = 0;
	while ((*s)[i] && (*s)[i] != ' ' && operand(data, s, i))
	{
		if ((*s)[i] == 34 || (*s)[i] == 39)
			i = vars_quote_check(&data->comm, s, i, data);
		i++;
	}
	if (write_arg(&data->comm, s, i, 0) == -100)
		error_mes_with_exit("Error malloc\n", data->data);
}

void	takeargs(t_comm *data, char **s)
{
	int	i;
	int	a;

	a = 1;
	i = 0;
	while ((*s)[i] && operand(data, s, i))
	{
		i = vars_quote_check(&data->args[a], s, i, data);
		if (i < 0)
			i = 0;
		if ((*s)[i] == ' ')
		{
			i = write_arg(&data->args[a], s, i, 0);
			if (i == -100)
				error_mes_with_exit("Error malloc\n", data->data);
			while ((*s)[0] && (*s)[0] == ' ')
				(*s)++;
			a++;
		}
		i++;
	}
	if (i > 0)
		if (write_arg(&data->args[a++], s, i, 0) == -100)
			error_mes_with_exit("Error malloc\n", data->data);
	if ((*s)[0])
		(*s)++;
	data->args[a] = NULL;
}

void	parser(t_data *data)
{
	t_comm	*p;
	char	*str;

	str = data->instr;
	while (*str)
	{
		p = addelem(data);
		if (!p)
			error_mes_with_exit("Error malloc\n", data);
		while (*str && *str == ' ')
			str++;
		takecommand(p, &str);
		while (*str && *str == ' ')
			str++;
		takeargs(p, &str);
	}
	p = data->comm;
	while (p)
	{
		printf("com: %s\n", p->comm);
		printf("arg: %s\n", p->args[0]);
		printf("arg: %s\n", p->args[1]);
		printf("arg: %s\n", p->args[2]);
		printf("oper: %s\n", p->oper);
		if (p->oper && !p->next)
			error_mes_with_exit("Error: There is no \
			command after the operator\n", data);
		else
			p = p->next;
	}
}
