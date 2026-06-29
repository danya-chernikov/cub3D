/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:19:30 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/29 03:47:30 by dchernik         ###   ########.fr       */
/*   Updated: 2026/06/05 20:24:05 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "libft.h"
# include "graphx.h"
# include "minimap.h"

# include <stdint.h>

# define PROG_NAME		"cube3D"
# define MAX_DELTA_TIME	0.05

typedef struct s_texture	t_texture;

/* Our main structre.
 *     gfx		  - graphics data: MLX syntax and the main image descriptor;
 *     delta_time - time elapsed since the previous frame, in seconds.
 *					Used to make movement and rotation independent of FPS;
 *     last_time  - timestamp of the previous frame, in seconds. Used to
 *					compute `delta_time` on the next frame */
typedef struct s_cube
{
	t_texture		*tex_files;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	t_uchar			**map;
	int				map_width;
	int				map_height;
	t_player		player;
	t_minimap		minimap;
	t_graph_data	gfx;
	double			delta_time;
	double			last_time;
	bool			fatal_error;
}	t_cube;

/* Contains file paths to
 * each texture (N, E, S, W).
 * We'll use the system constant
 * PATH_MAX to define the maximum
 * file path length */
typedef struct s_texture
{
	char	*north_path;
	char	*east_path;
	char	*south_path;
	char	*west_path;
	xpm_t	*north;
	xpm_t	*east;
	xpm_t	*south;
	xpm_t	*west;
}	t_texture;

/* cube.c */
t_cube	*parser_init(int argc, char **argv);
int		graphx_init(t_cube *cube);
void	game_loop(void *param);
void	handle_window_input(t_cube *cube);
void	clear_image(mlx_image_t *img, uint32_t color);

/* cube_time.c */
void	game_update_delta_time(t_cube *cube);
double	game_time_now(void);

/* texture.c */
int		textures_load(t_cube *cube);
int		texture_load_one(xpm_t **dst, char *path);

#endif
