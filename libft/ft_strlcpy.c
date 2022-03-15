/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:38:04 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/21 17:26:20 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char		*tmp_dst;
	const char	*tmp_src;
	size_t		i;

	tmp_dst = dst;
	tmp_src = src;
	i = dstsize - 1;
	if (dstsize != 0)
	{	
		while (i-- && *tmp_src)
			*tmp_dst++ = *tmp_src++;
		*tmp_dst = '\0';
	}
	return (ft_strlen(src));
}
