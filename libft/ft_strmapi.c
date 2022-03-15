/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:41:34 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/18 15:41:35 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	char			*str;
	unsigned int	size;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	size = ft_strlen((char *) s);
	str = ft_calloc(size + 1, sizeof(char));
	if (!(str))
		return (NULL);
	res = str;
	i = 0;
	while (*s)
		*str++ = (f)(i++, *s++);
	return (res);
}
