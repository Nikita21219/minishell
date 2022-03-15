/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:40:23 by bclarind          #+#    #+#             */
/*   Updated: 2021/10/22 16:29:19 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*prev;

	if (!(lst) || !(*lst))
		return ;
	current = *lst;
	while (current != NULL)
	{
		prev = current;
		current = current->next;
		ft_lstdelone(prev, del);
	}
	*lst = NULL;
}
