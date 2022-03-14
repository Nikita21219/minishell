/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:20:51 by bclarind          #+#    #+#             */
/*   Updated: 2022/03/14 17:09:45 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	int i;

	(void) argc;
	(void) argv;
	(void) env;
	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
}
