#include "../includes/minishell.h"

int	check_start(t_finfo *dt, char *filename)
{
	int	i;

	i = 0;
	while (dt->start[i] && filename[i])
	{
		if (dt->start[i] != filename[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_finish(t_finfo *dt, char *filename, int *arr_int)
{
	int	last_idx_filename;
	int	dt_finish_idx;
	(void) arr_int;

	last_idx_filename = ft_strlen(filename) - 1;
	dt_finish_idx = ft_strlen(dt->finish) - 1;
	while (last_idx_filename >= 0 && dt_finish_idx >= 0)
		if (filename[last_idx_filename--] != dt->finish[dt_finish_idx--])
			return (1);
	return (0);
}

char	*get_fname_without_start_and_finish(char *fname, t_finfo *dt)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_strdup(fname);
	if (res == NULL)
		return (NULL);
	while (dt->start && (res)[i] == dt->start[i])
	{
		res++;
		i++;
	}
	i = ft_strlen(res) - 1;
	j = ft_strlen(dt->finish) - 1;
	while (j >= 0 && dt->finish && dt->finish[j--])
		(res)[i--] = 0;
	return (res);
}

int	check_between(t_finfo *dt, char *filename)
{
	int		i;
	int		j;
	char	*fname;
	char	*tmp;

	i = 0;
	j = 0;
	filename = get_fname_without_start_and_finish(filename, dt);
	if (filename == NULL)
		return (1);
	fname = filename;
	while (dt->between[i])
	{
		tmp = filename;
		filename = ft_strnstr(filename, dt->between[i], ft_strlen(filename));
		if (filename == NULL)
			return (1);
		filename = ft_strdup(filename + ft_strlen(dt->between[i]));
		if (filename == NULL)
			return (1);
		i++;
	}
	return (0);
}
