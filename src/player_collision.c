/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:32:43 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/27 19:27:55 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "cube.h"

#include <math.h> /* For floor() */

/* Checks whether the player would collide with
 * any wall if placed at the given position
 * More info:
 * https://www.figma.com/design/MOGITOdwaCYQ11DAqgljlT/cub3D?
 * node-id=186-6&t=5nIXqabU7V6JhGvL-0 */
int	player_hits_wall(t_cube *cube, double x, double y)
{
	t_coord	min;
	t_coord	max;
	t_coord	cur_cell;
	double	r;

	r = cube->player.collision_radius;
	min.x = (int)floor(x - r);
	max.x = (int)floor(x + r);
	min.y = (int)floor(y - r);
	max.y = (int)floor(y + r);
	cur_cell.y = min.y;
	while (cur_cell.y <= max.y)
	{
		cur_cell.x = min.x;
		while (cur_cell.x <= max.x)
		{
			if (map_cell_is_wall(cube, cur_cell.x, cur_cell.y)
				&& circle_hits_tile(x, y, r, &cur_cell))
				return (true);
			++cur_cell.x;
		}
		++cur_cell.y;
	}
	return (false);
}

/* Checks whether a circle intersects a map tile. The player is
 * represented as a circle, while each wall cell is represented
 * as a square from (tx, ty) to (tx + 1, ty + 1) */
int	circle_hits_tile(double px, double py, double r, t_coord *tile)
{
	double	closest_x;
	double	closest_y;
	double	dx;
	double	dy;

	closest_x = clamp_double(px, tile->x, tile->x + 1.0);
	closest_y = clamp_double(py, tile->y, tile->y + 1.0);
	dx = px - closest_x;
	dy = py - closest_y;
	return (dx * dx + dy * dy < r * r);
}

/* Clamps a double value between the given minimum
 * and maximum bounds */
double	clamp_double(double val, double min, double max)
{
	if (val < min)
		return (min);
	if (val > max)
		return (max);
	return (val);
}
