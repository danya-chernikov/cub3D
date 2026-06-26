/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 18:09:24 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/26 12:02:32 by dchernik         ###   ########.fr       */
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

/* render.c */
void		render_scene(t_cube *cube);
void		render_wall_column(t_cube *cube, int x, double dist, int side);
uint32_t	render_wall_color(int side);
void		render_floor_ceiling(t_cube *cube);

/* raycast_setters.c */
void		ray_set_delta_dist(t_ray *ray);
void		ray_set_x_step(t_cube *cube, t_ray *ray);
void		ray_set_y_step(t_cube *cube, t_ray *ray);

/* raycast.c */
void		ray_init(t_cube *cube, t_ray *ray, int screen_x);
void		ray_cast(t_cube *cube, t_ray *ray);
double		ray_perp_dist(t_ray *ray);

#endif
