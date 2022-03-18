/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrast <rrast@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:20:51 by bclarind          #+#    #+#             */
/*   Updated: 2022/03/18 10:41:06 by rrast            ###   ########.fr       */
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
		// printf("%s\n", str);
		// printf("%s\n", data.test);
		add_history(str);
		free(str);
	}
}

int main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;
	printf("tets\n");
	minishell();
	return (0);
}
