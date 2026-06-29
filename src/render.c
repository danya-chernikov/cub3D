/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:47:21 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/27 19:38:54 by dchernik         ###   ########.fr       */
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
		render_wall_column(cube, x, dist, &ray);
		++x;
	}
}

/* Draws one wall column using the texture selected from the ray hit.
 * The column height comes from the perpendicular wall distance, while
 * `tex_x` and `tex_y` choose the correct pixels from the texture */
void	render_wall_column(t_cube *cube, int x, double dist, t_ray *ray)
{
	t_wall_column	col;
	t_tex_sample	sample;

	render_init_column(cube, &col, x, dist);
	render_init_tex(cube, ray, &col, &sample);
	render_draw_tex_column(cube, &col, &sample);
}

/* Initializes the screen-space data for one wall column. The wall height is
 * calculated from the perpendicular distance. The column is centered on the
 * screen and clamped to image bounds */
void	render_init_column(t_cube *cube, t_wall_column *col, int x, double dist)
{
	if (dist < 0.0001)
		dist = 0.0001;
	col->x = x;
	col->dist = dist;
	col->line_height = (int)(cube->gfx.win_height / dist);
	col->draw_start = -col->line_height / 2 + cube->gfx.win_height / 2;
	col->draw_end = col->line_height / 2 + cube->gfx.win_height / 2;
	if (col->draw_start < 0)
		col->draw_start = 0;
	if (col->draw_end >= cube->gfx.win_height)
		col->draw_end = cube->gfx.win_height - 1;
}

/* Initializes texture sampling for one wall column. `tex_x` is fixed for the
 * whole vertical column. `tex_step` tells how much to move in texture space
 * for each screen pixel drawn vertically */
void	render_init_tex(t_cube *cube, t_ray *ray, t_wall_column *col,
			t_tex_sample *sample)
{
	sample->tex = render_get_texture(cube, ray);
	sample->tex_x = render_tex_x(cube, ray, col->dist, sample->tex);
	sample->tex_step = (double)sample->tex->height / col->line_height;
	sample->tex_pos = (col->draw_start - cube->gfx.win_height / 2
			+ col->line_height / 2) * sample->tex_step;
}

/* Draws one textured vertical wall column. For each screen y
 * coordinate, the matching texture y coordinate is calculated
 * and the texture pixel is copied to the image */
void	render_draw_tex_column(t_cube *cube, t_wall_column *col,
			t_tex_sample *sample)
{
	int			y;
	int			tex_y;
	uint32_t	color;

	y = col->draw_start;
	while (y <= col->draw_end)
	{
		tex_y = (int)sample->tex_pos;
		color = texture_get_pixel(sample->tex, sample->tex_x, tex_y);
		put_pixel_safe(cube->gfx.img, col->x, y, color);
		sample->tex_pos += sample->tex_step;
		++y;
	}
}
