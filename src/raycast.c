/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 18:54:08 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/27 19:33:44 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "cube.h"

#include <math.h>

/* Initializes one ray for the given screen column.
 * `camera_x` maps the current screen column to the
 * camera plane: -1 means the left edge of the screen,
 * 0 means the center, 1 means the right edge. The ray
 * direction is computed as:
 * `player direction` + `camera plane offset`.
 * After that, DDA helper values are initialized.
 * Explanatory image:
 *     https://www.figma.com/design/MOGITOdwaCYQ11DAqgljlT/cub3D?
 *     node-id=188-2&t=nUC4xtcfh3nnW2BB-0 */
void	ray_init(t_cube *cube, t_ray *ray, int screen_x)
{
	double		camera_x;
	double		plane_len;
	double		player_fov_rad;
	t_dcoord	dir;
	t_dcoord	plane;

	camera_x = 2.0 * screen_x / (double)cube->gfx.win_width - 1.0;
	player_fov_rad = PLAYER_FOV_DEG * PI / 180.0;
	plane_len = tan(player_fov_rad / 2);
	dir.x = cos(cube->player.angle);
	dir.y = sin(cube->player.angle);
	plane.x = -dir.y * plane_len;
	plane.y = dir.x * plane_len;
	ray->dir.x = dir.x + plane.x * camera_x;
	ray->dir.y = dir.y + plane.y * camera_x;
	ray->map.x = (int)cube->player.pos.x;
	ray->map.y = (int)cube->player.pos.y;
	ray_set_delta_dist(ray);
	ray_set_x_step(cube, ray);
	ray_set_y_step(cube, ray);
}

/* Performs the DDA algorithm. The ray moves from
 * one map cell to the next until it reaches a wall.
 * At each step, we choose whether the next grid
 * boundary is closer on the x-axis or on the y-axis.
 * Explanatory image:
 *     https://www.figma.com/design/MOGITOdwaCYQ11DAqgljlT/cub3D?
 *     node-id=196-2&t=nUC4xtcfh3nnW2BB-0 */
void	ray_cast(t_cube *cube, t_ray *ray)
{
	while (!map_cell_is_wall(cube, ray->map.x, ray->map.y))
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
	}
}

/* Returns the perpendicular distance from
 * the player to the wall hit by the ray.
 * We subtract `delta_dist` because `side_dist`
 * has already been advanced one step after
 * entering the wall cell. This distance
 * is used to calculate the height of the
 * wall column on screen */
double	ray_perp_dist(t_ray *ray)
{
	if (ray->side == X_SIDE)
		return (ray->side_dist.x - ray->delta_dist.x);
	return (ray->side_dist.y - ray->delta_dist.y);
}
