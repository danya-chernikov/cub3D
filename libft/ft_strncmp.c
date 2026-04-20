/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:45:06 by dchernik          #+#    #+#             */
/*   Updated: 2024/09/30 18:45:07 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;
	size_t	min_len;

	if (n == 0)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	min_len = s1_len;
	if (s1_len > s2_len)
		min_len = s2_len;
	i = 0;
	while (i < n && i < min_len)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1_len > s2_len && n > s2_len)
		return ((unsigned char)s1[s2_len]);
	else if (s1_len < s2_len && n > s1_len)
		return (-1 * (unsigned char)s2[s1_len]);
	return (0);
}
