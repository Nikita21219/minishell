/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:37:49 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/18 15:37:51 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tmp_dst;
	const char	*tmp_src;
	char		*last_dst;
	const char	*last_src;

	tmp_dst = dst;
	tmp_src = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (tmp_dst < tmp_src)
		ft_memcpy(tmp_dst, tmp_src, len);
	else
	{
		last_dst = tmp_dst + (len - 1);
		last_src = tmp_src + (len - 1);
		while (len > 0)
		{
			*last_dst-- = *last_src--;
			len--;
		}
	}
	return (dst);
}
