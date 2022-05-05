#include "../includes/minishell.h"

int	connect_arrays(char ***temp, char ***args, char ***wild)
{
	int	j;
	int	x;

	j = -1;
	x = -1;
	while ((*args)[++j])
		(*temp)[j] = (*args)[j];
	while ((*wild)[++x])
		(*temp)[j++] = (*wild)[x];
	(*temp)[j] = NULL;
	(*temp)[j + 1] = NULL;
	free(*wild);
	free(*args);
	*args = *temp;
	return (-1);
}

int	check_wild(char ***args, char **wild)
{
	int		j;
	int		x;
	char	**temp;

	j = 0;
	x = 0;
	if (!wild)
		return (-3);
	while (wild[j])
		j++;
	while ((*args)[x])
		x++;
	temp = malloc(sizeof(char *) * (x + j + 2));
	if (!temp)
		return (-3);
	return (connect_arrays(&temp, args, &wild));
}

int	write_pos_wild(int **pos, int i, int a)
{
	int	*tmp;
	int	x;

	x = 0;
	tmp = malloc(sizeof(int) * (a + 1));
	if (!tmp)
		return (1);
	if (a > 1)
	{
		x = -1;
		while (++x < a - 1)
			tmp[x] = (*pos)[x];
	}
	tmp[x] = i;
	tmp[x + 1] = -1;
	if (*pos)
		free(*pos);
	*pos = tmp;
	return (0);
}

int	write_str_to_wild(char **str, int **pos)
{
	char	*tmp;
	int		i;
	int		n;
	int		qoute;

	i = -1;
	qoute = 0;
	while ((*str)[++i])
	{
		if ((*str)[i] == 34 || (*str)[i] == 39)
		{
			qoute++;
			n = 0;
			if (qoute % 2 == 0)
			{
				while ((*pos)[n] != -1 && (*pos)[n] <= i)
					n++;
				n--;
				while ((*pos)[++n] != -1)
					(*pos)[n] -= 2;
			}
		}
	}
	tmp = malloc(sizeof(char) * (i - qoute + 1));
	if (!tmp)
		return (1);
	i = -1;
	n = 0;
	while ((*str)[++i])
		if ((*str)[i] != 34 && (*str)[i] != 39)
			tmp[n++] = (*str)[i];
	tmp[n] = 0;
	if (*str)
		free(*str);
	*str = tmp;
	return (0);
}

int	skipping_quotes(char **s, int i)
{
	char	quote;

	quote = (*s)[i];
	if (!check_second_qoute(*s, i, quote))
		return (i);
	i++;
	while ((*s)[i] != quote)
		i++;
	return (i);
}

int	check_wildcard_arg(char **str, char **s, int i, t_comm *data)
{
	char	**wild;
	int		*pos;
	int		a;

	pos = NULL;
	a = 0;
	if ((*s)[i] != '*' || !data->comm)
		return (i);
	while ((*s)[i] && !ft_space((*s)[i]) && (*s)[i] != '<' && (*s)[i] != '>' \
		&& (*s)[i] != '|' && (*s)[i] != '&')
	{
		if ((*s)[i] == 34 || (*s)[i] == 39)
			i = skipping_quotes(s, i);
		if ((*s)[i] == '*')
			if (write_pos_wild(&pos, i, ++a))
				return (-3);
		i++;
	}
	if (write_arg(str, s, i) || write_str_to_wild(str, &pos))
		return (-3);
	printf("str to wild: %s\n", *str);
	i = 0;
	while (pos[i] != -1)
		printf("index: %d\n", pos[i++]);
	wild = wildcard(*str, pos);
	*str = NULL;
	free (pos);
	return (check_wild(&data->args, wild));
}
