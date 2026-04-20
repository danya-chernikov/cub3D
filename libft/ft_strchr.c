/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:42:25 by dchernik          #+#    #+#             */
/*   Updated: 2024/10/03 13:19:42 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*sptr;

	sptr = (char *)s;
	i = 0;
	while (sptr[i] != '\0')
	{
		if (sptr[i] == (char)c)
			return (sptr + i);
		i++;
	}
	if (c == '\0')
		return (sptr + i);
	return (NULL);
}
