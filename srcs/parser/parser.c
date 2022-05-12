#include "../../includes/minishell.h"

int	vars_quote_check(char **str, char **s, int i, t_comm *data)
{
	char	quote;

	if ((*s)[i] == '$' && (*s)[i + 1] \
		&& !ft_space((*s)[i + 1]) && (*s)[i + 1] != '=')
		return (takevar(s, str, data, i));
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
	i = check_wildcard_arg(str, s, i, data);
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

void	move_list(t_comm **p)
{
	t_comm	*temp;
	int		i;

	i = 0;
	temp = (*p)->next;
	(*p)->args = temp->args;
	temp->args = NULL;
	(*p)->comm = (*p)->args[1];
	while ((*p)->args[++i])
		(*p)->args[i] = (*p)->args[i + 1];
}

int	checkallcommands(t_comm **p)
{
	t_comm	*tmp;

	tmp = *p;
	if ((*p) && !(*p)->comm && ((*p)->oper[0] == '<' || (*p)->oper[0] == '>'))
		move_list(p);
	while (tmp)
	{
		if ((!tmp->comm && !(is_same_lines(tmp->oper, ">") || \
		is_same_lines(tmp->oper, ">>") || is_same_lines(tmp->oper, "<") \
		|| is_same_lines(tmp->oper, "<<"))) || (tmp->oper && !tmp->next))
		{
			printf("Parse error\n");
			errno = 22;
			return (1);
		}
		tmp = tmp->next;
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
	return (checkallcommands(&data->comm));
}
