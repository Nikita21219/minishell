#include "../../includes/minishell.h"

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

int	take_pos_for_wild(char **str, int **pos)
{
	int		n;
	int		i;

	n = 0;
	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == -42)
		{
			(*str)[i] = '*';
			if (write_pos_wild(pos, i, ++n))
				return (1);
		}
	}
	return (0);
}

int	write_arg_wild(char ***args, char **wild, int a)
{
	char	**tmp;
	int		x;
	int		y;

	x = 0;
	y = a;
	while (wild[x])
		x++;
	while ((*args)[y])
		y++;
	tmp = malloc(sizeof(char *) * (x + y + 1));
	if (!tmp)
		return (1);
	x = -1;
	while (++x != a)
		tmp[x] = (*args)[x];
	y = -1;
	while (wild[++y])
		tmp[x++] = wild[y];
	while ((*args)[++a])
		tmp[x++] = (*args)[a];
	tmp[x] = NULL;
	free(*args);
	*args = tmp;
	return (0);
}

int	check_wildcard_arg(t_comm *tmp)
{
	char	**wild;
	int		*pos;
	int		a;

	a = -1;
	while (tmp->args[++a])
	{
		pos = NULL;
		if (ft_strchr(tmp->args[a], -42))
		{
			if (take_pos_for_wild(&tmp->args[a], &pos))
				return (1);
			wild = wildcard(tmp->args[a], pos);
			free (pos);
			if (!wild)
				return (1);
			if (write_arg_wild(&tmp->args, wild, a))
			{
				free(wild);
				return (1);
			}
			free(wild);
		}
	}
	return (0);
}
