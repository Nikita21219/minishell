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

int	check_finish(t_finfo *dt, char *filename)
{
	int	last_idx_filename;
	int	dt_finish_idx;

	last_idx_filename = ft_strlen(filename) - 1;
	dt_finish_idx = ft_strlen(dt->finish) - 1;
	while (last_idx_filename >= 0 && dt_finish_idx >= 0 && \
	filename[last_idx_filename] && dt->finish[dt_finish_idx] && \
	dt->finish[dt_finish_idx] != '*')
		if (filename[last_idx_filename--] != dt->finish[dt_finish_idx--])
			return (1);
	return (0);
}

int	check_one_between(char *template, char *filename, int *j)
{
	int	i;

	i = 0;
	while (filename[*j] && template[i] != filename[*j])
		(*j)++;
	if (!filename[*j])
		return (1);
	while (template[i] && filename[*j])
		if (template[i++] != filename[(*j)++])
			return (1);
	return (0);
}

char	*get_fname_without_start_and_finish(char *fname, t_finfo *dt)
{
	char	*start;
	char	*finish;

	start = ft_strtrim(fname, dt->start);
	if (start == NULL)
		return (NULL);
	finish = ft_strtrim(start, dt->finish);
	free(start);
	return (finish);
}

int	check_between(t_finfo *dt, char *filename)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	filename = get_fname_without_start_and_finish(filename, dt);
	if (filename == NULL)
		return (1);
	while (dt->between[i])
	{
		if (check_one_between(dt->between[i++], filename, &j))
		{
			free(filename);
			filename = NULL;
			return (1);
		}
	}
	free(filename);
	filename = NULL;
	return (0);
}
