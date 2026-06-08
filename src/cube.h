/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:19:30 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/08 16:08:36 by dchernik         ###   ########.fr       */
/*   Updated: 2026/06/05 20:24:05 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include "graphx.h"

# include <stdint.h>
# include <sys/types.h>

typedef struct s_texture	t_texture;

/* Our main structre.
 *     gfx - graphics data: MLX syntax and the main image descriptor; */
typedef struct s_cube
{
	t_texture		*tex_files;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	u_char			**map;
	int				map_width;
	int				map_height;
	t_player		player;
	t_minimap		minimap;
	t_graph_data	gfx; // we'll definitey need it
}	t_cube;

/* Contains file paths to
 * each texture (N, E, S, W).
 * We'll use the system constant
 * PATH_MAX to define the maximum
 * file path length */
typedef struct s_texture
{
	const char	*north_path;
	const char	*east_path;
	const char	*south_path;
	const char	*west_path;
}	t_texture;

/* cube.c */
int		graphx_init(t_cube *cube);
void	game_loop(void *param);
void	clear_image(mlx_image_t *img, uint32_t color);

/* player.c */
void	player_init(t_cube *cube);
int		is_player_spawn(u_char c);
void	set_player_spawn(t_cube *cube, int x, int y);

#endif
