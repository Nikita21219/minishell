/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:41:06 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/18 22:12:51 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isinset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*mem;
	char	*res;
	char	*tmp_s1;
	char	*finish;
	int		len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 && ft_isinset(*s1, set))
		s1++;
	finish = (char *) s1 + ft_strlen((char *) s1) - 1;
	while (ft_isinset(*finish, set) && finish > s1)
		finish--;
	len = 0;
	tmp_s1 = (char *) s1;
	while (tmp_s1++ <= finish)
		len++;
	mem = ft_calloc(len + 1, sizeof(char));
	if (!(mem))
		return (NULL);
	res = mem;
	while (s1 <= finish)
		*mem++ = *s1++;
	return (res);
}
