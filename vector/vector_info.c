/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:48:15 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:48:16 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

bool	vector_empty(const t_vector *v)
{
	return (v->size == 0);
}

size_t	vector_size(const t_vector *v)
{
	return (v->size);
}

/* If '\0' wasn't found it will return
 * the vector size */
size_t	vector_strlen(const t_vector *v)
{
	size_t	len;
	t_uchar	*data;

	if (!v || !v->data)
		return (0);
	len = 0;
	data = (t_uchar *)v->data;
	while (len < v->size && data[len] != '\0')
		++len;
	return (len);
}

size_t	vector_capacity(const t_vector *v)
{
	return (v->capacity);
}
