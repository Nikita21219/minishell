/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:06:12 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:06:13 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_argv(int argc, char **argv, char **env, t_data *data)
{
	(void) data;
	(void) env;
	if (argc != 1)
	{
		printf("mini_hell: %s: No such file or directory\n", argv[1]);
		return (1);
	}
	return (0);
}

void	print_last_exit(void)
{
	printf("mini_hell: %d: %s\n", errno, strerror(errno));
}

void	fill_zero(int *arr, int k, int *j, char **res)
{
	(*j)--;
	if (*j < 0)
		*j = 0;
	else
		if (arr[--k] == (int)ft_strlen(res[*j]))
			res[*j][ft_strlen(res[*j])] = 0;
	res[(*j) + 1] = NULL;
}

int	only_slash(char *path)
{
	while (*path)
		if (*path++ != '/')
			return (0);
	return (1);
}

int	check_path(char *path)
{
	if (is_same_lines(path, ".."))
	{
		errno = 127;
		ft_fprintf(path, "command not found\n");
		return (errno);
	}
	else if (is_same_lines(path, "."))
	{
		errno = 2;
		ft_fprintf(path, "usage: . filename [arguments]\n");
		return (errno);
	}
	else if (only_slash(path))
	{
		errno = 126;
		ft_fprintf(path, "is a directory\n");
		return (errno);
	}
	return (0);
}
