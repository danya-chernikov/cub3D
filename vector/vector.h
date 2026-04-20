/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:48:10 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:48:10 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

/* Basic slow and UNSAFE vector implementation.
 * When we call vector_init() and pass it a capacity, it creates
 * a vector with that capacity. When adding new elements, if the
 * vector is about to overflow, it increases its current capacity
 * by DEFAULT_VEC_ENLARGER or by the value specified in the optional
 * third argument, enlarger, when overloading vector_init().
 *
 * DO NOT USE IT WITH RAW VOID!!! It's now finished yet
 * (and it's unlikely ot be of any use to us) */

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>

# define DEFAULT_VEC_ENLARGER	16

typedef unsigned char		t_uchar;
typedef unsigned short		t_ushort;
typedef unsigned int		t_uint;
typedef unsigned long		t_ul;
typedef long long			t_ll;
typedef unsigned long long	t_ull;
typedef long double			t_ld;

typedef enum e_data_type
{
	CHAR,
	U_CHAR,
	SHORT,
	U_SHORT,
	INT,
	U_INT,
	LONG,
	U_LONG,
	SIZE_T,
	LONG_LONG,
	U_LONG_LONG,
	FLOAT,
	DOUBLE,
	LONG_DOUBLE,
	VOID
}	t_data_type;

/* Just a vector.
 *     bsize     - vector capacity in bytes;
 *     esize     - size that occupies in memory
 *				   one vector's element, eguals
 *				   (bsize / capacity);
 *     front     - the first element;
 *     back      - the last element;
 *     data_type - should not be changed! */
typedef struct s_vector
{
	size_t		enlarger;
	size_t		capacity;
	size_t		bcapacity;
	size_t		size;
	size_t		esize;
	size_t		row_n;
	size_t		col_n;
	void		*front;
	void		*back;
	void		*data;
	t_data_type	data_type;

}	t_vector;

/* vector_main.c
 * Functions for creating, removing vector.
 *     vector_init(3 args) - fills nothing, just leaves memory data;
 *     vector_init(4 args) - fills all elements with `filler` */
int		vector_init(t_vector *v, t_data_type dtype, size_t cap);
int		vector_finit(t_vector *v, t_data_type dtype, size_t cap, int filler);
int		vector_minit(t_vector *v,
			t_data_type dtype,
			size_t row_n,
			size_t col_n);

/* vector_access.c
 * Functions for accessing vector's elements.
 * Does not change the vector content
 *     vector_at()    - accesses the element at index `ind`;
 *     vector_mat()   - accesses the element at index v->data[ri][ci];
 *     vector_front() - access the first element;
 *     vector_back()  - access the last element. */
void	*vector_at(const t_vector *v, size_t ind);
void	*vector_mat(const t_vector *v, size_t ri, size_t ci);
void	*vector_front(const t_vector *v);
void	*vector_back(const t_vector *v);

/* vector_info.c
 * Functions for returning vector's info
 *     vector_strlen() - treats vector as a string and
 *						 returns this string's length. */
bool	vector_empty(const t_vector *v);
size_t	vector_size(const t_vector *v);
size_t	vector_strlen(const t_vector *v);
size_t	vector_capacity(const t_vector *v);
void	vector_print_elem(const t_vector *v, size_t ind);
void	vector_print(const t_vector *v, char *delim);

/* vector_si.c
 * Functions that change the vector's content
 *     vector_si()  - change the value of the vector's
 *					  cell at index `ind`, i.e. v->data[ind]. */
void	vector_si(t_vector *v, size_t ind, void *val);

/* vector_msi.c
 *     vector_msi() - the same as vector_si() but for matrix. */
void	vector_msi(t_vector *v, size_t ri, size_t ci);

/* vector_stack.c */
int		vector_push_back_char(t_vector *v, char c);
void	vec_push_str(t_vector *v, const char *s);
int		vector_push_back(t_vector *v, void *val);

/* vector_stack2.c */
void	*vector_pop_back(t_vector *v);

/* vector_settings.c
 * Functions for changing vector's parameters.
 *     vector_reserve() - changes current vector capacity;
 * */
int		vector_reserve(t_vector *v, size_t new_cap);
void	vector_set_enlarger(t_vector *v, size_t enlarger);
void	vector_free(t_vector *v);

/* vector_utility.c */
void	*vector_memset(void *s, int c, size_t n);
void	*vector_realloc(void *ptr, size_t old_size, size_t new_size);

#endif
