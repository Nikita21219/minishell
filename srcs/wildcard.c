#include "../includes/minishell.h"

// void	*add_wild_el(t_wild **data)
// {
// 	(void) el;
// 	return (NULL);
// }

int	read_directory(DIR *dir, struct dirent **entry)
{
	*entry = readdir(dir);
	if (*entry == NULL)
		return (0);
	return (1);
}

t_wild  *wildcard(char *template)
{
	t_wild			*data;
	// char			*file;
	DIR				*dir;
	struct dirent	*entry;

	data = malloc(sizeof(t_wild));
	if (data == NULL)
		return (NULL);
	dir = opendir(fileinfo->path);
	if (dir == NULL)
		return (NULL);
	while (read_directory(dir, &entry))
	{
		// if ()
		printf("%s\n", entry->d_name);
	}
	closedir(dir);
	// if (is_right_str(template, file))
	// 	add_wild_el(&data, file);
	return (NULL);
}

int	main()
{
	t_wild *data;

	data = wildcard("./../minishell/*.txt");
	// sleep(10);
	return (0);
}

// c && cc srcs/wildcard.c libft/libft.a includes/minishell.h && ./a.out
