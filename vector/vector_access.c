/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:47:51 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:47:52 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	*vector_at(const t_vector *v, size_t ind)
{
	return (v->data + (ind * v->esize));
}

void	*vector_mat(const t_vector *v, size_t ri, size_t ci)
{
	return (v->data + (((v->col_n * ri) + ci)) * v->esize);
}

/* Access the first element */
void	*vector_front(const t_vector *v)
{
	return (v->front);
}

/* Access the last element */
void	*vector_back(const t_vector *v)
{
	return (v->back);
}
