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

	split_template = ft_split(template, '*');
	if (split_template == NULL)
		return (1);
	dt->start = NULL;
	dt->finish = NULL;
	dt->between = NULL;
	i = 0;
	if (template[i] != '*')
		dt->start = split_template[i++];
	last_idx_char = ft_strlen(template) - 1;
	last_idx_str = get_last_idx_str(split_template);
	if (template[last_idx_char] != '*')
	{
		dt->finish = split_template[last_idx_str];
		split_template[last_idx_str] = NULL;
	}
	dt->between = &split_template[i];
	free_arrs(split_template);
	return (0);
}

int	is_right_file(char *filename, char *template)
{
	t_finfo	*dt;

	if (filename[0] == '.' && template[0] != '.')
		return (0);
	dt = malloc(sizeof(t_finfo));
	if (dt == NULL)
		return (free_dt(dt));
	if (init_dt(dt, template))
		return (free_dt(dt));
	if (dt->start)
		if (check_start(dt, filename))
			return (free_dt(dt));
	// if (dt->finish)
	// 	if (check_finish(dt, filename))
	// 		return (free_dt(dt));
	// if (dt->between)
	// 	if (check_between(dt, filename))
	// 		return (free_dt(dt));
	free_dt(dt);
	return (1);
}

t_wild  *wildcard(char *template)
{
	t_wild			*data;
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	data = malloc(sizeof(t_wild));
	if (data == NULL)
	{
		closedir(dir);
		return (NULL);
	}
	while (read_directory(dir, &entry))
	{
		if (is_right_file(entry->d_name, template))
			printf("%s\n", entry->d_name);
			// wild_add_elem(&data, entry->d_name);
	}
	closedir(dir);
	return (data);
}

// int	main()
// {
// 	wildcard("s*s");
// 	// sleep(10);
// 	// char *answer = malloc(256);
// 	// t_wild	*test;

// 	// while (answer)
// 	// {
// 	// 	answer = readline("Enter command with wildcard: ");
// 	// 	add_history(answer);
// 	// 	test = wildcard(answer);
// 	// 	free(answer);
// 	// 	free(test);
// 	// 	sleep(10);
// 	// }
// 	return (0);
// }
