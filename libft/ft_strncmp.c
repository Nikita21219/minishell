/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:39:25 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/19 13:54:28 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 == *s2 && n-- && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	if (n == 0)
		return (0);
	if ((unsigned char) *s1 > (unsigned char) *s2)
		return (1);
	else if ((unsigned char) *s2 > (unsigned char) *s1)
		return (-1);
	return (0);
}
