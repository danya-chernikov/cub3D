/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:43:14 by dchernik          #+#    #+#             */
/*   Updated: 2024/10/03 02:44:26 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*empty_str_gen(void);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	i;
	char	*res_str;

	i = 0;
	slen = 0;
	while (s[slen] != '\0')
		slen++;
	if (start >= slen)
		return (empty_str_gen());
	if (len > slen - start)
		len = slen - start;
	res_str = (char *) malloc((len + 1) * sizeof(char));
	if (res_str == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		res_str[i] = s[start + i];
		i++;
	}
	res_str[i] = '\0';
	return (res_str);
}

static char	*empty_str_gen(void)
{
	char	*res_str;

	res_str = (char *)malloc(1);
	if (!res_str)
		return (NULL);
	res_str[0] = '\0';
	return (res_str);
}
