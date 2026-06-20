/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 13:56:40 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/20 17:32:37 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "cube.h"

#include <math.h> /* For sin() and cos() */

void	minimap_draw_fov(mlx_image_t *img, t_cube *cube)
{
	t_coord	center;
	t_coord	left_ray;
	t_coord	right_ray;
	double	half_fov;

	center = minimap_center(cube);
	half_fov = PLAYER_FOV_RAD / 2.0;
	left_ray = minimap_ray_end(cube, cube->player.angle - half_fov);
	right_ray = minimap_ray_end(cube, cube->player.angle + half_fov);
	draw_line(img, center, left_ray, COLOR_YELLOW);
	draw_line(img, center, right_ray, COLOR_YELLOW);
}

t_coord	minimap_center(t_cube *cube)
{
	t_coord	center;

	center.x = cube->minimap.pos.x + cube->minimap.size / 2;
	center.y = cube->minimap.pos.y + cube->minimap.size / 2;
	return (center);
}

/* tx - the value of parameter `t` at which the ray
 *		reaches a vertical grid boundary;
 * ty - the value of parameter `t` at which the ray
 *		reaches a horizontal grid boundary */
t_coord	minimap_ray_end(t_cube * cube, double angle)
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

double	ray_x_limit(t_cube *cube, t_coord center, double dir_x)
{
	if (dir_x > 0)
		return ((cube->minimap.pos.x + cube->minimap.size - 1 - center.x)
			/ dir_x);
	if (dir_x < 0)
		return ((cube->minimap.pos.x - center.x) / dir_x);
	return (INF);
}

double	ray_y_limit(t_cube *cube, t_coord center, double dir_y)
{
	if (dir_y > 0)
		return ((cube->minimap.pos.y + cube->minimap.size - 1 - center.y)
			/ dir_y);
	if (dir_y < 0)
		return ((cube->minimap.pos.y - center.y) / dir_y);
	return (INF);
}
