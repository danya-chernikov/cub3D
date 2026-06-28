/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:19:38 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/28 15:05:01 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stddef.h>

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

/* error.c */
void	print_error(const char *msg);
int		write_all(int fd, const char *s, size_t len);

#endif
