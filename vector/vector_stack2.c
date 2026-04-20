/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_stack2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:49:00 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:49:01 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/* On error returns NULL */
void	*vector_pop_back(t_vector *v)
{
	void	*ret;

	if (v->size == 0)
		return (NULL);
	ret = (t_uchar *)v->data + ((v->size - 1) * v->esize);
	--v->size;
	if (v->size == 0)
	{
		v->front = NULL;
		v->back = NULL;
	}
	else
	{
		v->front = v->data;
		v->back = (t_uchar *)v->data + (v->size - 1) * v->esize;
	}
	return (ret);
}
