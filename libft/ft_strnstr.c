/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:40:00 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/22 10:53:41 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;
	size_t	i;
	size_t	tmp_i;
	char	*tmp_haystack;

	if (*needle == '\0')
		return ((char *) haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		tmp_i = i;
		tmp_haystack = (char *) &haystack[i];
		while (haystack[tmp_i] == needle[j] && haystack[tmp_i] && tmp_i < len)
		{
			j++;
			tmp_i++;
		}
		if (needle[j] == '\0')
			return (tmp_haystack);
		i++;
	}
	return (NULL);
}
