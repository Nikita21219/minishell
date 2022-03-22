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
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	while ((*s)[i] && (*s)[i] != '|')
	{
		if ((*s)[i] == 34) // "
		{
			if (!data->args)
				data->args = ft_substr(*s, 0, i);
			else
			{
				tmp1 = data->args;
				data->args = ft_strjoin(tmp1, *s);
				free(tmp1);
			}
			while (i--)
				(*s)++;
			(*s)++;
			// printf("arg = %s!\n", data->args);
			// printf("s = %s\n", *s);
			// exit(1);
			if (ft_strchr(*s, 34))
			{
				i = 0;
				tmp1 = data->args;
				while ((*s)[i] != 34)
					i++;
				tmp2 = ft_substr(*s, 0, i++);
				data->args = ft_strjoin(tmp1, tmp2);
				while (i--)
					(*s)++;
				// printf("arg = %s!\n", data->args);
				// printf("s = %s\n", *s);
				// exit(1);
				free(tmp1);
				free(tmp2);
			}
		}
		i++;
	}
	if (!data->args)
		data->args = ft_substr(*s, 0, i);
	else
	{
		tmp1 = data->args;
		data->args = ft_strjoin(tmp1, *s);
		free(tmp1);
	}
	while (i--)
		(*s)++;
}

void	parser(t_data *data, char *s)
{
	t_data	*p;

	data = NULL;
	while (*s)
	{
		p = addelem(data);
		while (*s && *s == ' ')
			s++;
		if (!ft_isalpha(*s))
			exit (1);
		takecommand(p, &s);
		takeflags(p, &s);
		takeargs(p, &s);
		printf("args = !%s!\n", p->args);
		exit(1);
	}
}
