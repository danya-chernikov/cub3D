/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:43:04 by dchernik          #+#    #+#             */
/*   Updated: 2024/10/03 02:53:59 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*strnstr_alg(const char *b, const char *l, size_t len, size_t lsl);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	if (little[0] == '\0')
		return ((char *)big);
	little_len = ft_strlen(little);
	if (len >= little_len)
		return (strnstr_alg(big, little, len, little_len));
	return (NULL);
}

static char	*strnstr_alg(const char *b, const char *l, size_t len, size_t lslen)
{
	size_t	i;
	size_t	q;
	size_t	cnt;

	i = 0;
	while ((i + lslen <= len) && (b[i] != '\0'))
	{
		q = i;
		cnt = 0;
		while (b[q] == l[cnt])
		{
			if (cnt == lslen - 1)
				return ((char *)(b + i));
			q++;
			cnt++;
		}
		i++;
	}
	return (NULL);
}
