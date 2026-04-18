/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:42:43 by dchernik          #+#    #+#             */
/*   Updated: 2024/10/02 15:18:24 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	slen;
	size_t	nsize;

	i = 0;
	slen = 0;
	nsize = size;
	if (size != 0)
		nsize--;
	while (src[slen] != '\0')
		slen++;
	if (size > 0)
	{
		while (i < nsize && i < slen)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (slen);
}
