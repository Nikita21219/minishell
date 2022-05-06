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

char	*get_fname_without_start(char *fname, t_finfo *dt)
{
	int	i;

	i = 0;
	while (dt->start && *fname == dt->start[i])
	{
		fname++;
		i++;
	}
	return (ft_strdup(fname));
}

char	*get_fname_without_start_and_finish(char *fname, t_finfo *dt)
{
	int		i;
	int		j;
	char	*res;
	char	*trim_start;

	i = 0;
	j = 0;
	res = ft_strdup(fname);
	if (res == NULL)
		return (NULL);
	trim_start = get_fname_without_start(res, dt); //FIXME if not allocated
	i = ft_strlen(res) - 1;
	j = ft_strlen(dt->finish) - 1;
	while (j >= 0 && dt->finish && dt->finish[j--])
		(trim_start)[i--] = 0;
	free(res);
	return (trim_start);
}

int	check_between(t_finfo *dt, char *filename)
{
	int		i;
	int		j;
	char	*fname;
	char	*sub_str;
	char	*trim_str;

	i = 0;
	j = 0;
	fname = get_fname_without_start_and_finish(filename, dt);
	if (fname == NULL)
		return (1);
	trim_str = fname;
	while (dt->between[i])
	{
		sub_str = ft_strnstr(trim_str, dt->between[i], ft_strlen(trim_str));
		if (sub_str == NULL)
		{
			free(trim_str);
			return (1);
		}
		trim_str = ft_strdup(sub_str + ft_strlen(dt->between[i])); //FIXME if not allocated
		i++;
	}
	free(fname);
	return (0);
}
