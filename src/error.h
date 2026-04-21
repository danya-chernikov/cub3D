/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:19:38 by dchernik          #+#    #+#             */
/*   Updated: 2026/04/21 15:19:39 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/* Numerical limits definitions */
# define ERR_BUF_SIZE	512
# define WARN_BUF_SIZE	512

/* Parsing stage error messages */
# define COMMON_PARSE_ERR	"Parsing error"
# define MAP_OUTLINE_ERR	"Map's outline is not closed"
# define MAP_INV_CHAR_ERR	"Map contains an invalid character"
/* ... */

/* MLX error messages */
# define MLX_INIT_ERR		"Could not initialize mlx42 library"

/* These two functions were provided just
 * as an example (but they may still come
 * in handy) of a possible file organization
 * in our project, where each logical part
 * ('entity') is represented by its own header
 * file, while the implementation of such an
 * 'entity' is handled by one or several .c
 * source files (which is a very common thing btw) */
void	print_sys_error(const char *msg);
void	print_warning(const char *msg);

#endif
