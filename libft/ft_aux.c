/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:46:38 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:46:39 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	split_free(char ***res)
{
	size_t	i;

	i = 0;
	while ((*res)[i])
	{
		free((*res)[i]);
		++i;
	}
	free(*res);
}

size_t	split_size(char **res)
{
	size_t	i;

	i = 0;
	while (res[i])
		++i;
	return (i);
}
