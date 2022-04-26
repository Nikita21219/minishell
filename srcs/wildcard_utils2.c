#include "../includes/minishell.h"

int	check_parts(t_finfo *dt, char *filename)
{
	if (dt->start)
		if (check_start(dt, filename))
			return (free_dt(dt));
	if (dt->finish)
		if (check_finish(dt, filename))
			return (free_dt(dt));
	if (dt->between)
		if (check_between(dt, filename))
			return (free_dt(dt));
	free_dt(dt);
	return (1);
}
