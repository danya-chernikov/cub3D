/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:06:55 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/20 02:12:45 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "player.h"

/* All values are in px */
# define MINIMAP_SIZE		180 /* Length of minimap's side */
# define MINIMAP_TILE_SIZE	16
# define MINIMAP_POS_X		20
# define MINIMAP_POS_Y		20

/* Represents our 2D minimap.
 *     pos				- minimap's position in the main window;
 *     size				- minimap's size in pixels;
 *     tile_size	    - how many pixels one map cell occupies on the minimap;
 *     player_radius_px - player's visual radius on the minimap, in pixels. */
typedef struct s_minimap
{
	t_coord		pos;
	int			size;
	int			tile_size;
	int			player_radius_px;
	uint32_t	bg_color;
	uint32_t	wall_color;
	uint32_t	player_color;
}	t_minimap;

/* Helper structure that represents
 * a rectangle for drawing a minimap */
typedef struct s_rect
{
	t_coord		pos;
	int			w;
	int			h;
	uint32_t	color;
}	t_rect;

/* minimap.c */
void	minimap_init(t_cube *cube, t_coord pos);
void	minimap_draw(mlx_image_t *img, t_cube *cube);
void	minimap_draw_player(mlx_image_t *img, t_cube *cube);
void	minimap_draw_background(mlx_image_t *img, t_minimap *minimap);
void	minimap_fill_rect(mlx_image_t *img, t_minimap *minimap, t_rect r);

/* minimap_walls.c */
void	minimap_draw_walls(mlx_image_t *img, t_cube *cube);
void	minimap_draw_wall(mlx_image_t *img, t_cube *cube, int mx, int my);
int		map_cell_is_wall(t_cube *cube, int x, int y);
int		map_cell_is_visible_wall(t_cube *cube, int x, int y);
int		map_row_len(t_uchar *row);

/* minimap_fov.c */
void	minimap_draw_fov(mlx_image_t *img, t_cube *cube);
t_coord	minimap_center(t_cube *cube);
t_coord	minimap_ray_end(t_cube * cube, double angle);
double	ray_x_limit(t_cube *cube, t_coord center, double dir_x);
double	ray_y_limit(t_cube *cube, t_coord center, double dir_y);

/* minimap_utils.c */
void	minimap_put_pixel(mlx_image_t *img, t_minimap *minimap,
			t_coord *pos, uint32_t color);
bool	in_minimap(t_minimap *minimap, int x, int y);
t_coord	map_cell_to_minimap(t_cube *cube, int mx, int my);
t_coord	world_to_minimap(t_cube *cube, double wx, double wy);

#endif
