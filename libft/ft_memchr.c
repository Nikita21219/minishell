/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:39:38 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/21 16:49:59 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;

	str = (char *) s;
	if (c == 0 && n == 0)
		return (NULL);
	if (c == '\0')
	{
		while (*str)
			str++;
		return (str);
	}
	while (n--)
	{
		if (*str == (char) c)
			return (str);
		str++;
	}
	return (NULL);
}
