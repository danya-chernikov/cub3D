/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:42:28 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/17 23:06:59 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*sbuf;
	size_t	i;

	sbuf = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (sbuf == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		sbuf[i] = s[i];
		i++;
	}
	sbuf[i] = '\0';
	return (sbuf);
}
