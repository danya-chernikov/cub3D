/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_si.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:48:48 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:48:49 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

static void	vector_si1(t_vector *v, size_t ind, void *val);
static void	vector_si2(t_vector *v, size_t ind, void *val);

/* Of course, you're allowed to put only
 * elements of the same type into the vector */
void	vector_si(t_vector *v, size_t ind, void *val)
{
	if (ind >= v->size)
		return ;
	vector_si1(v, ind, val);
	vector_si2(v, ind, val);
}

static void	vector_si1(t_vector *v, size_t ind, void *val)
{
	if (v->data_type == CHAR)
		((char *)v->data)[ind] = ((char *)val)[0];
	else if (v->data_type == U_CHAR)
		((t_uchar *)v->data)[ind] = ((t_uchar *)val)[0];
	else if (v->data_type == SHORT)
		((short *)v->data)[ind] = *((short *)val);
	else if (v->data_type == U_SHORT)
		((t_ushort *)v->data)[ind] = *((t_ushort *)val);
	else if (v->data_type == INT)
		((int *)v->data)[ind] = *((int *)val);
	else if (v->data_type == U_INT)
		((t_uint *)v->data)[ind] = *((t_uint *)val);
	else if (v->data_type == LONG)
		((long *)v->data)[ind] = *((long *)val);
	else if (v->data_type == U_LONG)
		((t_ul *)v->data)[ind] = *((t_ul *)val);
}

static void	vector_si2(t_vector *v, size_t ind, void *val)
{
	if (v->data_type == SIZE_T)
		((size_t *)v->data)[ind] = *((size_t *)val);
	if (v->data_type == LONG_LONG)
		((t_ll *)v->data)[ind] = *((t_ll *)val);
	else if (v->data_type == U_LONG_LONG)
		((t_ull *)v->data)[ind] = *((t_ull *)val);
	else if (v->data_type == FLOAT)
		((float *)v->data)[ind] = *((float *)val);
	else if (v->data_type == DOUBLE)
		((double *)v->data)[ind] = *((double *)val);
	else if (v->data_type == LONG_DOUBLE)
		((t_ld *)v->data)[ind] = *((t_ld *)val);
	else if (v->data_type == VOID)
		((void **)v->data)[ind] = (void *)val;
}
