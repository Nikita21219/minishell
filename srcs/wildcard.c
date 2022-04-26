#include "../includes/minishell.h"

int	read_directory(DIR *dir, struct dirent **entry)
{
	*entry = readdir(dir);
	if (*entry == NULL)
		return (0);
	return (1);
}

int	get_last_idx_str(char **split_template)
{
	int	i;

	i = 0;
	while (split_template[i] && split_template[i + 1])
		i++;
	return (i);
}

int	init_dt(t_finfo *dt, char *template)
{
	char	**split_template;
	int		i;
	int		last_idx_str;
	int		last_idx_char;

	if (initial_var(&split_template, dt, template))
		return (1);
	i = 0;
	if (template[i] != '*')
		if (init_dt_start(dt, split_template[i++], &split_template))
			return (1);
	last_idx_char = ft_strlen(template) - 1;
	last_idx_str = get_last_idx_str(split_template);
	if (template[last_idx_char] != '*')
		if (init_dt_finish(dt, split_template[last_idx_str], \
		&split_template, last_idx_str))
			return (1);
	if (split_template[i])
		if (init_dt_between(dt, &split_template, &i))
			return (1);
	free_arrs(split_template);
	return (0);
}

int	is_right_file(char *filename, char *template)
{
	t_finfo	*dt;
	int		i;
	int		count;

	if (filename[0] == '.' && template[0] != '.')
		return (0);
	dt = malloc(sizeof(t_finfo));
	if (dt == NULL)
		return (free_dt(dt));
	if (init_dt(dt, template))
		return (free_dt(dt));
	i = 0;
	count = 0;
	while (dt->between && i < len(dt->between) && dt->between[i])
		count += ft_strlen(dt->between[i++]);
	if (ft_strlen(filename) < ft_strlen(dt->start) + \
	ft_strlen(dt->finish) + count)
		return (free_dt(dt));
	return (check_parts(dt, filename));
}

t_wild	*wildcard(char *template)
{
	t_wild			*data;
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	data = NULL;
	while (read_directory(dir, &entry))
		if (is_right_file(entry->d_name, template))
			if (wild_add_elem(&data, entry->d_name))
				continue ;
	closedir(dir);
	return (data);
}
