#include "../includes/minishell.h"

int	take_pos_for_wild(char **str, int *qoute, int **pos)
{
	char	qt;
	int		n;
	int		i;

	n = 0;
	i = -1;
	while ((*str)[++i])
	{
		if (((*str)[i] == 34 || (*str)[i] == 39) \
			&& check_second_qoute(*str, i, (*str)[i]))
		{
			qt = (*str)[i++];
			while ((*str)[i] != qt)
				i++;
			(*qoute) += 2;
		}
		if ((*str)[i] == '*')
			if (write_pos_wild(pos, i - (*qoute), ++n))
				return (-1);
	}
	return (i);
}

int	write_str_to_wild(char **str, int **pos)
{
	char	*tmp;
	int		i;
	int		n;
	int		qoute;

	qoute = 0;
	i = take_pos_for_wild(str, &qoute, pos);
	if (i < 0)
		return (1);
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
		i++;
	}
	if (write_arg(str, s, i) || write_str_to_wild(str, &pos))
		return (-3);
	wild = wildcard(*str, pos);
	*str = NULL;
	free (pos);
	return (check_wild(&data->args, wild));
}
