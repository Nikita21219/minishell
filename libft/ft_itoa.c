/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:41:25 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/18 15:41:26 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_zero(void)
{
	char	*res;

	res = ft_calloc(2, sizeof(char));
	if (!(res))
		return (NULL);
	*res = '0';
	return (res);
}

int	len_count(int n)
{
	int	count;

	count = 0;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*write_in_res(char *res, int flag, int n)
{
	while (n)
	{
		*res-- = n % 10 * flag + 48;
		n = n / 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		count;
	int		flag;

	count = 0;
	flag = 1;
	if (n == 0)
		return (ft_zero());
	else if (n < 0)
	{
		count++;
		flag = -1;
	}
	count += len_count(n);
	res = ft_calloc(count + 1, sizeof(char));
	if (!(res))
		return (NULL);
	res += count - 1;
	res = write_in_res(res, flag, n);
	if (flag < 0)
	{
		*res = '-';
		return (res);
	}
	return (res + 1);
}
