/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:20:49 by dchernik          #+#    #+#             */
/*   Updated: 2025/02/07 15:03:20 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*lptr;

	lptr = (t_list *)malloc(1 * sizeof(t_list));
	if (lptr == NULL)
		return (NULL);
	lptr->content = content;
	lptr->next = NULL;
	return (lptr);
}
