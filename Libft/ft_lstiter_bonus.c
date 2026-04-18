/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:23:33 by dchernik          #+#    #+#             */
/*   Updated: 2025/05/04 17:50:58 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*nptr;

	if ((lst == NULL) || (f == NULL))
		return ;
	nptr = lst;
	while (nptr != NULL)
	{
		(*f)(nptr->content);
		nptr = nptr->next;
	}
}
