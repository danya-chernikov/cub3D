/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:49:07 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:49:08 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	*vector_memset(void *s, int c, size_t n)
{
	t_uchar	*buf;
	size_t	i;

	buf = (t_uchar *)s;
	i = 0;
	while (i < n)
	{
		buf[i] = c;
		++i;
	}
	return (s);
}

void	*vector_realloc(void *ptr, size_t old_size, size_t new_size)
{
	t_uchar	*new_ptr;
	size_t	copy_size;
	size_t	i;

	if (!new_size && ptr)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = (t_uchar *)malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (!ptr)
		return (new_ptr);
	copy_size = new_size;
	if (old_size < new_size)
		copy_size = old_size;
	i = 0;
	while (i < copy_size)
	{
		new_ptr[i] = ((t_uchar *)(ptr))[i];
		++i;
	}
	free(ptr);
	return (new_ptr);
}
