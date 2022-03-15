/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:40:57 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/18 15:40:58 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*mem;
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	mem = ft_calloc(\
		ft_strlen((char *) s1) + ft_strlen((char *) s2) + 1, \
		sizeof(char));
	if (!(mem))
		return (NULL);
	res = mem;
	while (*s1)
		*mem++ = *s1++;
	while (*s2)
		*mem++ = *s2++;
	return (res);
}
