/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:48:57 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:48:58 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

static void	push_back1(t_vector *v, void *val);
static void	push_back2(t_vector *v, void *val);

int	vector_push_back_char(t_vector *v, char c)
{
	return (vector_push_back(v, &c));
}

void	vec_push_str(t_vector *v, const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		vector_push_back_char(v, s[i]);
		++i;
	}
}

int	vector_push_back(t_vector *v, void *val)
{
	void	*tmp;

	if (v->size + 1 > v->capacity)
	{
		v->capacity += v->enlarger;
		tmp = vector_realloc(v->data, v->bcapacity, v->capacity * v->esize);
		if (!tmp)
			return (0);
		v->data = tmp;
		v->bcapacity = v->capacity * v->esize;
	}
	push_back1(v, val);
	push_back2(v, val);
	++v->size;
	v->front = v->data;
	v->back = (t_uchar *)v->data + (v->size - 1) * v->esize;
	return (1);
}

static void	push_back1(t_vector *v, void *val)
{
	if (v->data_type == CHAR)
		((char *)v->data)[v->size] = ((char *)val)[0];
	else if (v->data_type == U_CHAR)
		((t_uchar *)v->data)[v->size] = ((t_uchar *)val)[0];
	else if (v->data_type == SHORT)
		((short *)v->data)[v->size] = *((short *)val);
	else if (v->data_type == U_SHORT)
		((t_ushort *)v->data)[v->size] = *((t_ushort *)val);
	else if (v->data_type == INT)
		((int *)v->data)[v->size] = *((int *)val);
	else if (v->data_type == U_INT)
		((t_uint *)v->data)[v->size] = *((t_uint *)val);
	else if (v->data_type == LONG)
		((long *)v->data)[v->size] = *((long *)val);
	else if (v->data_type == U_LONG)
		((t_ul *)v->data)[v->size] = *((t_ul *)val);
}

static void	push_back2(t_vector *v, void *val)
{
	if (v->data_type == SIZE_T)
		((size_t *)v->data)[v->size] = *((size_t *)val);
	if (v->data_type == LONG_LONG)
		((t_ll *)v->data)[v->size] = *((t_ll *)val);
	else if (v->data_type == U_LONG_LONG)
		((t_ull *)v->data)[v->size] = *((t_ull *)val);
	else if (v->data_type == FLOAT)
		((float *)v->data)[v->size] = *((float *)val);
	else if (v->data_type == DOUBLE)
		((double *)v->data)[v->size] = *((double *)val);
	else if (v->data_type == LONG_DOUBLE)
		((t_ld *)v->data)[v->size] = *((t_ld *)val);
	else if (v->data_type == VOID)
		((void **)v->data)[v->size] = (void *)val;
}
