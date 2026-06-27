/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 16:56:33 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/27 12:55:00 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "cube.h"

#include <math.h> /* For floor() */

/* Selects the wall texture hit by the current ray.
 * X_SIDE means the ray hit a vertical wall side;
 * Y_SIDE means the ray hit a horizontal wall side.
 * The step direction tells which face of the wall
 * cell was entered:
 * west/east for X_SIDE and north/south for Y_SIDE */
mlx_texture_t	*render_get_texture(t_cube *cube, t_ray *ray)
{
	if (ray->side == X_SIDE)
	{
		if (ray->step.x > 0)
			return (&cube->tex_files->west->texture);
		return (&cube->tex_files->east->texture);
	}
	if (ray->step.y > 0)
		return (&cube->tex_files->north->texture);
	return (&cube->tex_files->south->texture);
}

/* Returns one pixel from an MLX texture in RGBA format.
 * Coordinates are clamped to avoid reading outside the texture */
uint32_t	texture_get_pixel(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*p;
	size_t	i;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= (int)tex->width)
		x = tex->width - 1;
	if (y >= (int)tex->height)
		y = tex->height - 1;
	i = (y * tex->width + x) * tex->bytes_per_pixel;
	p = tex->pixels;
	return ((p[i] << 24) | (p[i + 1] << 16) | (p[i + 2] << 8) | p[i + 3]);
}

/* Computes the horizontal texture coordinate for the wall hit. For vertical
 * wall sides, the hit position changes along y. For horizontal wall sides,
 * the hit position changes along x */
int	render_tex_x(t_cube *cube, t_ray *ray, double dist, mlx_texture_t *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == X_SIDE)
		wall_x = cube->player.pos.y + dist * ray->dir.y;
	else
		wall_x = cube->player.pos.x + dist * ray->dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == X_SIDE && ray->dir.x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == Y_SIDE && ray->dir.y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
