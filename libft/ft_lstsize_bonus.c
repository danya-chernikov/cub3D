/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:22:10 by dchernik          #+#    #+#             */
/*   Updated: 2025/02/07 19:32:20 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*nptr;
	int		size;

	if (lst == NULL)
		return (0);
	size = 0;
	nptr = lst;
	while (nptr != NULL)
	{
		nptr = nptr->next;
		size++;
	}
	return (size);
}
