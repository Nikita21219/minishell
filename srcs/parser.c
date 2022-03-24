#include "../includes/minishell.h"

void	takecommand(t_data *data, char **s)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	str = *s;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		i++;
	tmp = ft_substr(str, 0, i);
	data->comm = ft_strtrim(tmp, " ");
	free(tmp);
	while (i--)
		(*s)++;
}

void	takeflags(t_data *data, char **s)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	str = *s;
	while (str[i] && (str[i] == '-' || str[i] == ' '))
	{
		while (str[i] && str[i] != ' ')
			i++;
		i++;
	}
	tmp = ft_substr(str, 0, i);
	data->flags = ft_split(tmp, ' ');
	free(tmp);
	while (i--)
		(*s)++;
}

void	takeargs(t_data *data, char **s)
{
	int		i;
	char	quote;

	i = 0;
	while ((*s)[i] && (*s)[i] != '|')
	{
		if ((*s)[i] == 34 || (*s)[i] == 39)
		{
			quote = (*s)[i];
			if (check_second_qoute(*s, i, quote))
			{
				i = write_arg(data, s, i);
				(*s)++;
				i = check_quote(s, data, quote);
			}
		}
		i++;
	}
	write_arg(data, s, i);
}

void	parser(t_data *data, char *s, char **env)
{
	t_data	*p;

	data = NULL;
	while (*s)
	{
		p = addelem(data, env);
		while (*s && *s == ' ')
			s++;
		if (!ft_isalpha(*s))
			exit (1);
		takecommand(p, &s);
		takeflags(p, &s);
		takeargs(p, &s);
		printf("command = !%s!\n", p->comm);
		printf("flags = !%s!\n", p->flags[0]);
		printf("flags = !%s!\n", p->flags[1]);
		printf("args = !%s!\n", p->args);
	}
	exit(1);
}
