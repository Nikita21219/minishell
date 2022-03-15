/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:37:27 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/21 16:36:16 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*tmp_dst;
	const char	*tmp_src;

	i = 0;
	tmp_dst = dst;
	tmp_src = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i++ < n)
		*tmp_dst++ = *tmp_src++;
	return (dst);
}
