/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 13:56:40 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/27 19:34:20 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "cube.h"

#include <math.h> /* For sin() and cos() */

/* Draws the player's field of view on the minimap.
 * The FOV is represented by two rays: the left border
 * and the right border of the player's viewing angle */
void	minimap_draw_fov(mlx_image_t *img, t_cube *cube)
{
	t_coord	center;
	t_coord	left_ray;
	t_coord	right_ray;
	double	half_fov;
	double	player_fov_rad;

	center = minimap_center(cube);
	player_fov_rad = PLAYER_FOV_DEG * PI / 180.0;
	half_fov = player_fov_rad / 2.0;
	left_ray = minimap_ray_end(cube, cube->player.angle - half_fov);
	right_ray = minimap_ray_end(cube, cube->player.angle + half_fov);
	draw_line(img, center, left_ray, COLOR_YELLOW);
	draw_line(img, center, right_ray, COLOR_YELLOW);
}

/* Returns the screen-space center of
 * the minimap. Since the player is
 * always drawn in the center of the
 * minimap, this point also represents
 * the player's visual position */
t_coord	minimap_center(t_cube *cube)
{
	t_coord	center;

	center.x = cube->minimap.pos.x + cube->minimap.size / 2;
	center.y = cube->minimap.pos.y + cube->minimap.size / 2;
	return (center);
}

/* Computes the endpoint of a FOV ray on the minimap
 * border. The ray starts at the minimap center and
 * goes in the direction defined by angle. The ray
 * can leave the square minimap through either a
 * vertical edge, left or right, or a horizontal edge,
 * top or bottom.
 * t.x - stores the value of parameter `t` at which
 *		 the ray reaches a vertical edge of the minimap;
 * t.y - stores the value of parameter `t` at which the
 *		 ray reaches a horizontal edge of the minimap.
 * The smaller `t` is used because it represents the
 * closest minimap edge in the ray's direction. That
 * gives us the first border point hit by the ray, so
 * the drawn line stays inside the minimap */
t_coord	minimap_ray_end(t_cube *cube, double angle)
{
	t_coord		center;
	t_coord		end;
	t_dcoord	t;
	double		dir_x;
	double		dir_y;

	center = minimap_center(cube);
	dir_x = cos(angle);
	dir_y = sin(angle);
	t.x = ray_x_limit(cube, center, dir_x);
	t.y = ray_y_limit(cube, center, dir_y);
	if (t.x < t.y)
	{
		end.x = center.x + (int)round(dir_x * t.x);
		end.y = center.y + (int)round(dir_y * t.x);
	}
	else
	{
		end.x = center.x + (int)round(dir_x * t.y);
		end.y = center.y + (int)round(dir_y * t.y);
	}
	return (end);
}

/* Returns the value of parameter `t` at which the ray reaches
 * the left or right edge of the minimap. If `dir_x` is zero,
 * the ray is vertical and will never reach a vertical edge
 * through its x component, so INF is returned */
double	ray_x_limit(t_cube *cube, t_coord center, double dir_x)
{
	if (dir_x > 0)
		return ((cube->minimap.pos.x + cube->minimap.size - 1 - center.x)
			/ dir_x);
	if (dir_x < 0)
		return ((cube->minimap.pos.x - center.x) / dir_x);
	return (INF);
}

/* Returns the value of parameter `t` at which the ray reaches
 * the top or bottom edge of the minimap. If `dir_y` is zero,
 * the ray is horizontal and will never reach a horizontal edge
 * through its y component, so INF (very huge value) is returned */
double	ray_y_limit(t_cube *cube, t_coord center, double dir_y)
{
	if (dir_y > 0)
		return ((cube->minimap.pos.y + cube->minimap.size - 1 - center.y)
			/ dir_y);
	if (dir_y < 0)
		return ((cube->minimap.pos.y - center.y) / dir_y);
	return (INF);
}
