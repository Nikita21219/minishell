#include "../includes/minishell.h"

int	connect_array(char ***args, char **wild, int i)
{
	int		j;
	int		x;
	char	**temp;

	j = 0;
	x = 0;
	if (!wild)
		return (-1);
	if (is_same_lines((*args)[i], *wild))
		return (i);
	while (wild[j])
		j++;
	while ((*args)[x])
		x++;
	temp = malloc(sizeof(char *) * (x + j + 1));
	if (!temp)
	{
		j = 0;
		while (wild[j])
			free(wild[j++]);
		free(wild);
		return (-1);
	}
	j = -1;
	x = -1;
	while (++j < i)
		temp[j] = (*args)[j];
	while (wild[++x])
		temp[j] = wild[x];
	x = i;
	while ((*args)[x])
	{
		temp[j] = (*args)[x];
		j++;
		x++;
	}
	temp[j] = NULL;
	free(wild);
	return (i);
}

int	check_wildcard_arg(char ***args)
{
	int		i;

	i = 0;
	while ((*args)[i])
	{
		if (ft_strchr((*args)[i], '*'))
			i = connect_array(args, wildcard((*args)[i]), i);
		if (i < 0)
			return (1);
		i++;
	}
	return (0);
}
