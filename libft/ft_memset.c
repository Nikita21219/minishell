/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 13:49:25 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/08 13:49:39 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	size_t	i;
	char	*tmp_buf;

	tmp_buf = destination;
	i = 0;
	while (i < n)
	{
		*tmp_buf = c;
		tmp_buf++;
		i++;
	}
	return (destination);
}
