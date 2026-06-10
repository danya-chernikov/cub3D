/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:19:38 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/10 12:20:43 by adeestev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/* Numerical limits definitions */
# define ERR_BUF_SIZE	512
# define WARN_BUF_SIZE	512

/* Parsing stage error messages */
# define MAP_OUTLINE_ERR		"Map's outline is not closed"
# define MAP_INV_CHAR_ERR		"Map contains an invalid character"
# define MAP_ISLAND_ERR			"Disconnected map found"
# define MAP_MALLOC_ERR			"Memory allocation failed"
# define MAP_PLAYER_DIR_ERR		"Player's direction is invalid"
# define MAP_ONE_PLAYER_ERR		"Map must contain exactly one player"
# define MAP_NOT_LAST_ERR		"Map is not last element in file"
# define MAP_REPEATED_ERR		"Repeated elements in file"
# define MAP_INV_PATH_FILE_ERR	"Texture path or file is invalid"
# define MAP_INV_IDENT_ERR		"Identifier is invalid"
# define MAP_TEXT_MISS_ERR		"Texture missing in file"
# define MAP_COL_MISS_ERR		"Color missing in file"
# define MAP_MISS_MAP_ERR		"Missing map in file"
# define MAP_INV_ELEM_ERR		"Missing or invalid configuration elements"
# define MAP_INV_COL_RANGE_ERR	"Color values are out of range"
# define MAP_INV_EXT_ERR		"Invalid file extension. Expected .cub"
# define MAP_OPEN_ERR			"Cannot open file"
# define MAP_NO_CONT_ERR		"No content in file"

/* MLX error messages */
# define MLX_INIT_ERR			"Could not initialize mlx42 library"

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

void	print_error(const char *msg);

#endif
