/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 18:09:24 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/27 12:53:37 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "graphx.h"

# define X_SIDE	0
# define Y_SIDE	1

typedef struct s_cube	t_cube;

/* One ray cast from the player through one screen column.
 * Basically, I'm trying to implement Lodev's approach here:
 *     https://lodev.org/cgtutor/raycasting.html
 * Some of my drawings explaining how DDA works:
 * Ray emision:
 *     https://www.figma.com/design/MOGITOdwaCYQ11DAqgljlT/cub3D?
 *     node-id=188-2&t=nUC4xtcfh3nnW2BB-0
 * DDA:
 *     https://www.figma.com/design/MOGITOdwaCYQ11DAqgljlT/cub3D?
 *     node-id=196-2&t=nUC4xtcfh3nnW2BB-0
 * Variables description:
 *     dir			- ray direction in world coordinates;
 *     delta_dist	- distance from one x/y grid line to the next;
 *     side_dist	- distance from the player to the next x/y grid line;
 *     map			- current map cell checked by DDA;
 *     step			- DDA step direction, either -1 or +1;
 *     side			- X_SIDE if a x-side was hit, Y_SIDE if a y-side was hit */
typedef struct s_ray
{
	t_dcoord	dir;
	t_dcoord	delta_dist;
	t_dcoord	side_dist;
	t_coord		map;
	t_coord		step;
	int			side;
}	t_ray;

/* Stores the data needed to draw one
 * vertical wall column on the screen.
 *     x			- screen column where the wall
 *					  slice is drawn;
 *     line_height	- projected wall height (in screen
 *					  pixels) calculated from perpendicular
 *					  distance;
 *     draw_start	- first screen y coordinate of
 *					  the wall slice;
 *     draw_end		- last screen y coordinate of
 *					  the wall slice;	
 *     dist			- perpendicular distance from
 *					  the player to the wall */
typedef struct s_wall_column
{
	int		x;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	dist;
}	t_wall_column;

/* Stores texture sampling data for one
 * vertical wall column.
 *     tex		- MLX texture selected for the
 *				  wall side hit by the ray;
 *     tex_x	- fixed horizontal coordinate
 *				  inside the texture;
 *     tex_pos	- current vertical position
 *				  inside the texture;
 *     tex_step - amount added to `tex_pos` for
 *				  each screen pixel drawn */
typedef struct s_tex_sample
{
	mlx_texture_t	*tex;
	int				tex_x;
	double			tex_pos;
	double			tex_step;
}	t_tex_sample;

/* render.c */
void			render_scene(t_cube *cube);
void			render_wall_column(t_cube *cube, int x, double dist,
					t_ray *ray);
void			render_init_column(t_cube *cube, t_wall_column *col,
					int x, double dist);
void			render_init_tex(t_cube *cube, t_ray *ray, t_wall_column *col,
					t_tex_sample *sample);
void			render_draw_tex_column(t_cube *cube, t_wall_column *col,
					t_tex_sample *sample);

/* render2.c */
void			render_floor_ceiling(t_cube *cube);

/* render_texture.c */
mlx_texture_t	*render_get_texture(t_cube *cube, t_ray *ray);
uint32_t		texture_get_pixel(mlx_texture_t *tex, int x, int y);
int				render_tex_x(t_cube *cube, t_ray *ray, double dist,
					mlx_texture_t *tex);

/* raycast_setters.c */
void			ray_set_delta_dist(t_ray *ray);
void			ray_set_x_step(t_cube *cube, t_ray *ray);
void			ray_set_y_step(t_cube *cube, t_ray *ray);

/* raycast.c */
void			ray_init(t_cube *cube, t_ray *ray, int screen_x);
void			ray_cast(t_cube *cube, t_ray *ray);
double			ray_perp_dist(t_ray *ray);

#endif
