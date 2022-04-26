#include "../includes/minishell.h"

int	wild_add_elem(char ***arr, char *file, int i)
{
	take_arg_mass(arr, i);
	(*arr)[i] = ft_strdup(file);
	take_arg_mass(arr, i + 1);
	return (0);
}

void	free_parts(t_finfo *dt, int *i)
{
	if (dt->finish)
	{
		free(dt->finish);
		dt->finish = NULL;
	}
	if (dt->start)
	{
		free(dt->start);
		dt->start = NULL;
	}
	if (dt->between)
	{
		while (dt->between[*i])
		{
			free(dt->between[*i]);
			dt->between[(*i)++] = NULL;
		}
		free(dt->between);
		dt->between = NULL;
	}
}

int	free_dt(t_finfo *dt)
{
	int	i;

	i = 0;
	if (dt)
	{
		free_parts(dt, &i);
		free(dt);
		dt = NULL;
	}
	return (0);
}
