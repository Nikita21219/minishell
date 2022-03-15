/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:41:16 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/22 16:27:02 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_pointers(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static size_t	len_char(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s == c)
		s++;
	while (*s && *s++ != c)
		i++;
	return (i);
}

static void	*mem_free(char **s)
{
	while (*s)
	{
		*s = NULL;
		free(*s);
		s++;
	}
	free(s);
	s = NULL;
	return (NULL);
}

static char	**main_logic(int i, char const *s, char c, char	**res)
{
	char	**arr;
	char	*str;

	arr = res;
	while (i--)
	{
		while (*s && *s == c)
			s++;
		str = ft_calloc(len_char(s, c) + 1, sizeof(char));
		if (!(str))
			return (mem_free(arr));
		*res++ = str;
		while (*s && *s != c)
			*str++ = *s++;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**res;

	if (!s)
		return (NULL);
	i = len_pointers(s, c);
	res = ft_calloc(i + 1, sizeof(char *));
	if (!(res))
		return (NULL);
	return (main_logic(i, s, c, res));
}
