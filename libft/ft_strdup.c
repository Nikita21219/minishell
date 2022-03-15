/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:40:36 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/18 15:40:37 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*res;
	char	*tmp_str;

	size = ft_strlen((char *) s1);
	res = ft_calloc(size + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	tmp_str = res;
	while (*s1)
		*tmp_str++ = *s1++;
	*tmp_str = 0;
	return (res);
}
