/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:48:32 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:48:33 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

static void	print_elem1(const t_vector *v, size_t ind);
static void	print_elem2(const t_vector *v, size_t ind);

/* In case if vector data type is VOID it prints the pointer.
 * printf() treat both float and double the same, but just
 * to improve visual clarity, let's print float with %f and
 * double with %lf */
void	vector_print_elem(const t_vector *v, size_t ind)
{
	print_elem1(v, ind);
	print_elem2(v, ind);
}

void	vector_print(const t_vector *v, char *delim)
{
	size_t	i;

	i = 0;
	while (i < v->size)
	{
		vector_print_elem(v, i);
		printf("%s", delim);
		++i;
	}
}

static void	print_elem1(const t_vector *v, size_t ind)
{
	if (v->data_type == CHAR)
		printf("%c", ((char *)v->data)[ind]);
	else if (v->data_type == U_CHAR)
		printf("%c", ((t_uchar *)v->data)[ind]);
	else if (v->data_type == SHORT)
		printf("%hd", ((short *)v->data)[ind]);
	else if (v->data_type == U_SHORT)
		printf("%hu", ((t_ushort *)v->data)[ind]);
	else if (v->data_type == INT)
		printf("%d", ((int *)v->data)[ind]);
	else if (v->data_type == U_INT)
		printf("%u", ((t_uint *)v->data)[ind]);
	else if (v->data_type == LONG)
		printf("%ld", ((long *)v->data)[ind]);
	else if (v->data_type == U_LONG)
		printf("%lu", ((t_ul *)v->data)[ind]);
}

static void	print_elem2(const t_vector *v, size_t ind)
{
	if (v->data_type == SIZE_T)
		printf("%zu", ((size_t *)v->data)[ind]);
	if (v->data_type == LONG_LONG)
		printf("%lld", ((t_ll *)v->data)[ind]);
	else if (v->data_type == U_LONG_LONG)
		printf("%llu", ((t_ull *)v->data)[ind]);
	else if (v->data_type == FLOAT)
		printf("%f", ((float *)v->data)[ind]);
	else if (v->data_type == DOUBLE)
		printf("%lf", ((double *)v->data)[ind]);
	else if (v->data_type == LONG_DOUBLE)
		printf("%Lf", ((t_ld *)v->data)[ind]);
	else if (v->data_type == VOID)
		printf("%p", v->data + ind);
}
