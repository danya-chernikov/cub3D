/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:48:21 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:48:22 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

static void	set_bcap1(t_vector *v);
static void	set_bcap2(t_vector *v);

/* Yeah, I know we could specify the vector's data type size
 * by passing sizeof() directly as the second argument in the
 * caller, but I think the approach we're using at the moment
 * could be useful in the future. On success returns 1 */
int	vector_init(t_vector *v, t_data_type dtype, size_t cap)
{
	if (cap == 0)
		return (0);
	v->capacity = cap;
	v->enlarger = DEFAULT_VEC_ENLARGER;
	v->data_type = dtype;
	v->size = 0;
	set_bcap1(v);
	set_bcap2(v);
	v->esize = v->bcapacity / v->capacity;
	v->data = malloc(v->bcapacity);
	if (!v->data)
		return (0);
	v->front = NULL;
	v->back = NULL;
	return (1);
}

/* The same as previous but fills all the
 * elements with `filler` On success returns 1 */
int	vector_finit(t_vector *v, t_data_type dtype, size_t cap, int filler)
{
	if (cap == 0)
		return (0);
	v->capacity = cap;
	v->enlarger = DEFAULT_VEC_ENLARGER;
	v->data_type = dtype;
	v->size = cap;
	set_bcap1(v);
	set_bcap2(v);
	v->esize = v->bcapacity / v->capacity;
	v->data = malloc(v->bcapacity);
	if (!v->data)
		return (0);
	vector_memset(v->data, filler, v->bcapacity);
	v->front = v->data;
	v->back = v->data + (v->size - 1) * v->esize;
	return (1);
}

int	vector_minit(t_vector *v, t_data_type dtype, size_t row_n, size_t col_n)
{
	if (row_n == 0 || col_n == 0)
		return (0);
	v->row_n = row_n;
	v->col_n = col_n;
	v->capacity = v->row_n * v->col_n;
	v->enlarger = DEFAULT_VEC_ENLARGER;
	v->data_type = dtype;
	v->size = 0;
	set_bcap1(v);
	set_bcap2(v);
	v->esize = v->bcapacity / v->capacity;
	v->data = malloc(v->bcapacity);
	if (!v->data)
		return (0);
	v->front = NULL;
	v->back = NULL;
	return (1);
}

static void	set_bcap1(t_vector *v)
{
	if (v->data_type == CHAR)
		v->bcapacity = v->capacity * sizeof (char);
	else if (v->data_type == U_CHAR)
		v->bcapacity = v->capacity * sizeof (t_uchar);
	else if (v->data_type == SHORT)
		v->bcapacity = v->capacity * sizeof (short);
	else if (v->data_type == U_SHORT)
		v->bcapacity = v->capacity * sizeof (t_ushort);
	else if (v->data_type == INT)
		v->bcapacity = v->capacity * sizeof (int);
	else if (v->data_type == U_INT)
		v->bcapacity = v->capacity * sizeof (t_uint);
	else if (v->data_type == LONG)
		v->bcapacity = v->capacity * sizeof (long);
	else if (v->data_type == U_LONG)
		v->bcapacity = v->capacity * sizeof (t_ul);
}

static void	set_bcap2(t_vector *v)
{
	if (v->data_type == SIZE_T)
		v->bcapacity = v->capacity * sizeof (size_t);
	else if (v->data_type == LONG_LONG)
		v->bcapacity = v->capacity * sizeof (t_ll);
	else if (v->data_type == U_LONG_LONG)
		v->bcapacity = v->capacity * sizeof (t_ull);
	else if (v->data_type == FLOAT)
		v->bcapacity = v->capacity * sizeof (float);
	else if (v->data_type == DOUBLE)
		v->bcapacity = v->capacity * sizeof (double);
	else if (v->data_type == LONG_DOUBLE)
		v->bcapacity = v->capacity * sizeof (t_ld);
	else if (v->data_type == VOID)
		v->bcapacity = v->capacity * sizeof (void);
}
