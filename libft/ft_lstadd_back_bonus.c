/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:21:30 by dchernik          #+#    #+#             */
/*   Updated: 2025/02/08 00:02:14 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*nptr;

	if ((lst == NULL) || (new == NULL))
		return ;
	nptr = ft_lstlast(*lst);
	if (nptr)
		nptr->next = new;
	else
		*lst = new;
}
