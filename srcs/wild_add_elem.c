#include "../includes/minishell.h"

int	wild_add_elem(t_wild **dt, char *file)
{
	t_wild	*tmp_dt;
	t_wild	*new;

	new = malloc(sizeof(t_wild));
	if (new == NULL)
		return (1);
	new->file = ft_strdup(file);
	if (new->file == NULL)
	{
		free(new);
		return (1);
	}
	new->next = NULL;
	if (*dt == NULL)
		*dt = new;
	else
	{
		tmp_dt = *dt;
		while (tmp_dt->next)
			tmp_dt = tmp_dt->next;
		tmp_dt->next = new;
	}
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
