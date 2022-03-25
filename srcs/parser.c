#include "../includes/minishell.h"

int	vars_quote_check(char **str, char **s, int i)
{
	char	quote;

	if ((*s)[i] == '$')
		i = takevar(s, str, i);
	if ((*s)[i] == 34 || (*s)[i] == 39)
	{
		quote = (*s)[i];
		if (check_second_qoute(*s, i, quote))
		{
			i = write_arg(str, s, i, 0);
			(*s)++;
			i = check_quote(s, str, quote);
		}
	}
	return (i);
}

void	takecommand(t_data *data, char **s)
{
	int		i;

	i = 0;
	while ((*s)[i] && (*s)[i] != ' ' && operand(data, s, i))
	{
		if ((*s)[i] == 34 || (*s)[i] == 39)
			i = vars_quote_check(&data->comm, s, i);
		i++;
	}
	write_arg(&data->comm, s, i, 0);
}

void	takeargs(t_data *data, char **s)
{
	int	i;
	int	a;

	a = 1;
	i = 0;
	while ((*s)[i] && operand(data, s, i))
	{
		i = vars_quote_check(&data->args[a], s, i);
		if (i < 0)
			i = 0;
		if ((*s)[i] == ' ')
		{
			i = write_arg(&data->args[a], s, i, 0);
			while ((*s)[0] && (*s)[0] == ' ')
				(*s)++;
			a++;
		}
		i++;
	}
	if (i > 0)
		write_arg(&data->args[a++], s, i, 0);
	if ((*s)[0])
		(*s)++;
	data->args[a] = NULL;
}

void	parser(t_data *data, char *s, t_envr *env)
{
	t_data	*p;

	data = NULL;
	while (*s)
	{
		p = addelem(data, env);
		while (*s && *s == ' ')
			s++;
		takecommand(p, &s);
		while (*s && *s == ' ')
			s++;
		takeargs(p, &s);
		printf("command = !%s!\n", p->comm);
		printf("args = !%s!\n", p->args[0]);
		printf("args = !%s!\n", p->args[1]);
		printf("args = !%s!\n", p->args[2]);
		printf("args = !%s!\n", p->args[3]);
		printf("oper = !%s!\n", p->oper);
	}
	exit(1);
}
