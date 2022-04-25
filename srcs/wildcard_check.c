#include "../includes/minishell.h"

int check_start(t_finfo *dt, char *filename)
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

int	check_finish(t_finfo *dt, char *filename)
{
	int	last_idx_filename;
	int	dt_finish_idx;

	last_idx_filename = ft_strlen(filename) - 1;
	dt_finish_idx = ft_strlen(dt->finish) - 1;
	while (filename[last_idx_filename] && dt->finish[dt_finish_idx] && dt->finish[dt_finish_idx] != '*' && last_idx_filename >= 0 && dt_finish_idx >= 0)
		if (filename[last_idx_filename--] != dt->finish[dt_finish_idx--])
			return (1);
	return (0);
}

int	check_one_between(char *template, char *filename, int *j)
{
	int	i = 0;
	int	flag;

	i = 0;
	while (filename[*j] && template[i] != filename[*j])
		(*j)++;
	if (!filename[*j])
		return (1);
	flag = 0;
	while (template[i] && filename[*j])
	{
		// if (template[i] == filename[*j])
		// 	flag = 1;
		if (template[i++] != filename[(*j)++])
			return (1);
		// (*j)++;
	}
	// if (!flag)
	// 	return (1);
	return (0);
}

char	*get_fname_without_start_and_finish(char *fname, t_finfo *dt)
{
	char	*start;
	char	*finish;

	start = ft_strtrim(fname, dt->start);
	if (start == NULL)
		return (NULL);
	finish = ft_strtrim(start, dt->finish); //FIXME leaks
	return (finish);
}

int	check_between(t_finfo *dt, char *filename)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dt->between[i])
	{
		filename = get_fname_without_start_and_finish(filename, dt);
		if (filename == NULL)
			return (1);
		if (check_one_between(dt->between[i++], filename, &j))
			return (1);
		// j++;
	}
	return (0);
}

int	free_dt(t_finfo *dt)
{
	int	i;

	i = 0;
	if (dt)
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
			while (dt->between[i])
			{
				free(dt->between[i]);
				dt->between[i++] = NULL;
			}
			free(dt->between);
			dt->between = NULL;
		}
		free(dt);
		dt = NULL;
	}
	return (0);
}
