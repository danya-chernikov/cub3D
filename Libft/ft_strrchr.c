/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:43:08 by dchernik          #+#    #+#             */
/*   Updated: 2024/10/02 17:21:18 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		pos;
	char	*sptr;

	sptr = (char *)s;
	i = 0;
	pos = -1;
	while (sptr[i] != '\0')
	{
		if (sptr[i] == (char)c)
			pos = i;
		i++;
	}
	if (c == '\0')
		pos = i;
	if (pos >= 0)
		return (sptr + pos);
	return (NULL);
}
