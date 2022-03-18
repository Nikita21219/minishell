/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:20:51 by bclarind          #+#    #+#             */
/*   Updated: 2022/03/18 10:17:32 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char *str, t_data *data)
{
	data->args = ft_split(str, ' ');
}

void	minishell(void)
{
	char	*str;
	t_data	data;
	int		i;

	while (1)
	{
		i = 0;
		str = readline(READLINE_RED "mini_hell$ " TERM_RESET);
		parser(str, &data);
		while (data.args[i])
			printf("%s\n", data.args[i++]);
		add_history(str);
		free(str);
	}
}

int main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;

	if (check_argv(argc, argv))
		return (1);
	minishell();
	return (0);
}
