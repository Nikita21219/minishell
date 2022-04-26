#include "../includes/minishell.h"

int	connect_arrays(int i, char ***temp, char ***args, char ***wild)
{
	int	j;
	int	x;

	j = -1;
	x = -1;
	while (++j < i)
		(*temp)[j] = (*args)[j];
	while ((*wild)[++x])
		(*temp)[j++] = (*wild)[x];
	x = ++i;
	i = j - 1;
	while ((*args)[x])
		(*temp)[j++] = (*args)[x++];
	(*temp)[j] = NULL;
	free(*wild);
	free(*args);
	*args = *temp;
	return (i);
}

int	check_wild(char ***args, char **wild, int i)
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
		free_arrs(wild);
		printf("Error malloc in parse\n");
		errno = 12;
		return (-1);
	}
	return (connect_arrays(i, &temp, args, &wild));
}

int	check_wildcard_arg(char ***args)
{
	int		i;

	i = 0;
	while ((*args)[i])
	{
		if ((*args)[i][0] == '*' || ft_strchr((*args)[i], '*') != NULL)
			i = check_wild(args, wildcard((*args)[i]), i);
		if (i < 0)
			return (1);
		i++;
	}
	return (0);
}
