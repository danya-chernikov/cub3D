/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:23:41 by dchernik          #+#    #+#             */
/*   Updated: 2025/02/08 00:05:23 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/* This function must use del() in case of a memory allocation error when
 * creating a new list! That's what the del() function is for! It is
 * necessary to delete all the previously allocated nodes along with their
 * contents if ft_lstnew() fails to allocate memory for a new node */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list_head;
	t_list	*nptr;

	if ((lst == NULL) || (del == NULL))
		return (NULL);
	new_list_head = NULL;
	while (lst)
	{
		if (f != NULL)
			nptr = ft_lstnew(f(lst->content));
		else
			nptr = ft_lstnew(lst->content);
		if (nptr == NULL)
		{
			ft_lstclear(&new_list_head, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list_head, nptr);
		lst = lst->next;
	}
	return (new_list_head);
}
