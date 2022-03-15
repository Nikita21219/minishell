/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:40:46 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/21 20:25:17 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*mem;
	char	*res;

	if (!s)
		return (NULL);
	if (start > (unsigned int) ft_strlen(s))
		len = 0;
	if (len < ft_strlen(s))
		mem = ft_calloc(len + 1, sizeof(char));
	else
		mem = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!(mem))
		return (NULL);
	res = mem;
	while (*s++ && start)
		start--;
	s--;
	while (*s && len--)
		*mem++ = *s++;
	return (res);
}
