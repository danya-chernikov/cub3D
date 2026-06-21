/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:20:36 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/21 02:36:22 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "cube.h"
#include "libft.h"

#include <math.h>

/* Computes how far the ray must travel to
 * cross one vertical grid line and one
 * horizontal grid line. If one ray direction
 * component is zero, the ray is parallel
 * to that axis and would never cross the
 * corresponding grid lines, so INF is used */
void	ray_set_delta_dist(t_ray *ray)
{
	if (ray->dir.x == 0.0)
		ray->delta_dist.x = INF;
	else
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = INF;
	else
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
}

/* Sets the horizontal DDA step. If the ray goes left,
 * `step.x` is -1 and `side_dist.x` is the distance from
 * the player to the left side of the current cell.
 * If the ray goes right, `step.x` is 1 and `side_dist.x`
 * is the distance to the right side of the current cell */
void	ray_set_x_step(t_cube *cube, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (cube->player.pos.x - ray->map.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - cube->player.pos.x)
			* ray->delta_dist.x;
	}
}

/* Sets the vertical DDA step. If the ray goes up,
 * `step.y` is -1 and `side_dist.y` is the distance
 * from the player to the top side of the current
 * cell. If the ray goes down, `step.y` is 1 and
 * `side_dist.y` is the distance to the bottom side
 * of the current cell */
void	ray_set_y_step(t_cube *cube, t_ray *ray)
{
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (cube->player.pos.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - cube->player.pos.y)
			* ray->delta_dist.y;
	}
}
