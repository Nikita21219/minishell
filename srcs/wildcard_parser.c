#include "../includes/minishell.h"

// int	connect_arrays(int i, char ***temp, char ***args, char ***wild)
// {
// 	int	j;
// 	int	x;

// 	j = -1;
// 	x = -1;
// 	while (++j < i)
// 		(*temp)[j] = (*args)[j];
// 	while ((*wild)[++x])
// 		(*temp)[j++] = (*wild)[x];
// 	x = ++i;
// 	i = j - 1;
// 	while ((*args)[x])
// 		(*temp)[j++] = (*args)[x++];
// 	(*temp)[j] = NULL;
// 	free(*wild);
// 	free(*args);
// 	*args = *temp;
// 	return (i);
// }

// int	check_wild(char ***args, char **wild, int i)
// {
// 	int		j;
// 	int		x;
// 	char	**temp;

// 	j = 0;
// 	x = 0;
// 	if (!wild)
// 		return (-1);
// 	if (is_same_lines((*args)[i], *wild))
// 		return (i);
// 	while (wild[j])
// 		j++;
// 	while ((*args)[x])
// 		x++;
// 	temp = malloc(sizeof(char *) * (x + j + 1));
// 	if (!temp)
// 	{
// 		free_arrs(wild);
// 		printf("Error malloc in parse\n");
// 		errno = 12;
// 		return (-1);
// 	}
// 	return (connect_arrays(i, &temp, args, &wild));
// }

// int	check_wildcard_arg(char ***args)
// {
// 	int		i;

// 	i = 0;
// 	while ((*args)[i])
// 	{
// 		if ((*args)[i][0] == '*' || ft_strchr((*args)[i], '*') != NULL)
// 			i = check_wild(args, wildcard((*args)[i]), i);
// 		if (i < 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

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

int	write_str_to_wild(char **str)
{
	char	*tmp;
	int		i;
	int		n;
	int		qoute;

	i = -1;
	qoute = 0;
	while ((*str)[++i])
		if ((*str)[i] == 34 || (*str)[i] == 39)
			qoute++;
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

int	check_wildcard_arg(char **str, char **s, int i, t_comm *data)
{
	char	quote;
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
		{
			quote = (*s)[i];
			if (!check_second_qoute(*s, i, quote))
				return (i);
			i++;
			while ((*s)[i] != quote)
				i++;
		}
		if ((*s)[i] == '*')
			if (write_pos_wild(&pos, i, ++a))
				return (-3);
		i++;
	}
	if (write_arg(str, s, i) || write_str_to_wild(str))
		return (-3);
	return (i);
}
