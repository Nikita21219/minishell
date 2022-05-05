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
	if (a > 0)
	{
		x = -1;
		while (++x <= a - 1)
			tmp[x] = (*pos)[x];
	}
	tmp[x] = i;
	tmp[x + 1] = -1;
	if (*pos)
		free(*pos);
	*pos = tmp;
	return (0);
}
