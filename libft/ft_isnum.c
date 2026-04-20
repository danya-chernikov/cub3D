/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:45:22 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:45:23 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isnum(const char *s)
{
	size_t	i;

	if (!s || !s[0])
		return (false);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		++i;
	if (!s[i])
		return (false);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (false);
		++i;
	}
	return (true);
}
