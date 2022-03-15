/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:38:22 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/21 17:28:29 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const char	*tmp_src;
	char		*tmp_dst;
	size_t		tmp_size;

	tmp_src = src;
	tmp_dst = dst;
	tmp_size = size;
	if (size < ft_strlen(dst) + 1)
		return (ft_strlen(src) + size);
	while (*tmp_dst && tmp_size)
	{
		tmp_dst++;
		tmp_size--;
	}
	return (ft_strlen(dst) + ft_strlcpy(tmp_dst, tmp_src, tmp_size));
}
