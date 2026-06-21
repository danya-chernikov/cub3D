/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:47:21 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/21 02:46:18 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "cube.h"

/* Casts one ray for each vertical
 * screen column and draws the
 * corresponding wall slice */
void	render_scene(t_cube *cube)
{
	t_ray	ray;
	double	dist;
	int		x;

	x = 0;
	while (x < cube->gfx.win_width)
	{
		ray_init(cube, &ray, x);
		ray_cast(cube, &ray);
		dist = ray_perp_dist(&ray);
		render_wall_column(cube, x, dist, ray.side);
		++x;
	}
}

/* Draws one vertical wall column on the screen. The column height
 * is inversely proportional to the distance: the smaller the distance,
 * the taller the wall appears. `draw_start` and `draw_end` are clamped
 * to the window bounds so we never try to draw outside the image */
void	render_wall_column(t_cube *cube, int x, double dist, int side)
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			y;
	uint32_t	color;

	if (dist <	0.0001)
		dist = 0.0001;
	line_height = (int)(cube->gfx.win_height / dist);
	draw_start = -line_height / 2 + cube->gfx.win_height / 2;
	draw_end = line_height / 2 + cube->gfx.win_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= cube->gfx.win_height)
		draw_end = cube->gfx.win_height - 1;
	color = render_wall_color(side);
	y = draw_start;
	while (y <= draw_end)
	{
		put_pixel_safe(cube->gfx.img, x, y, color);
		++y;
	}
}

/* Returns a temporary wall color for the
 * current ray hit. Since we do not render
 * textures yet, we use two different
 * gray colors to make the 3D view easier
 * to read.
 * side == X_SIDE means that the ray hit
 * a vertical side of a map cell, while
 * side == Y_SIDE means that it hit a
 * horizontal side. Drawing one side
 * slightly darker creates a simple shading
 * effect and helps us see the wall direction
 * and check that the DDA algorithm works
 * correctly. Later, this temporary coloring
 * will be replaced by texture selection
 * depending on the wall orientation */
uint32_t	render_wall_color(int side)
{
	if (side == X_SIDE)
		return (COLOR_GRAY);
	return (COLOR_LIGHT_GRAY);
}
