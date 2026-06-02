/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphx_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:11:53 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/02 17:53:39 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphx.h"

#include <math.h>
#include <stdlib.h>

static void	bresenham_update_error(t_coord *p0, int *err,
	int deltas[], int steps[]);
static void	draw_girdling_rect(mlx_image_t *img, t_line *line,
	int offset_x, int offset_y);

/* Draws a line between two points p0 and p1 using Bresenham's algorithm.
 *     deltas[0] - dx;
 *     deltas[1] - dy;
 *     steps[0]  - sx;
 *     steps[1]  - sy. */
void	draw_line(mlx_image_t *img, t_coord p0, t_coord p1, uint32_t color)
{
	int	deltas[2];
	int	steps[2];
	int	err;

	steps[BR_SX] = -1;
	steps[BR_SY] = -1;
	deltas[BR_DX] = abs(p1.x - p0.x);
	if (p0.x < p1.x)
		steps[BR_SX] = 1;
	deltas[BR_DY] = -abs(p1.y - p0.y);
	if (p0.y < p1.y)
		steps[BR_SY] = 1;
	err = deltas[BR_DX] + deltas[BR_DY];
	while (1)
	{
		put_pixel_safe(img, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		bresenham_update_error(&p0, &err, deltas, steps);
	}
}

/* Updates accumulated error term.
 *     deltas[0] - dx;
 *     deltas[1] - dy;
 *     steps[0]  - sx;
 *     steps[1]  - sy. */
static void	bresenham_update_error(t_coord *p0, int *err,
	int deltas[], int steps[])
{
	int	e2;

	e2 = 2 * *err;
	if (e2 >= deltas[BR_DY])
	{
		*err += deltas[BR_DY];
		p0->x += steps[BR_SX];
	}
	if (e2 <= deltas[BR_DX])
	{
		*err += deltas[BR_DX];
		p0->y += steps[BR_SY];
	}
}

/* Draws a line with a specified thickness. We represent our
 * line as a vector (p0; p1). Then we calculate a normal vector
 * (nx; ny) to the (p0; p1). After that, we normalize the normal
 * vector (nx; ny) to unit length and stretch it by multiplying
 * its coordinates by half of the desired line thickness. We
 * call this final transformed vector the 'offset vector', with
 * coordinates (offset_x; offset_y).
 * Next, we draw a rectangle around the initial line represented
 * by p0 and p1. To get one side of this rectangle, we move both
 * endpoints of the line by the (offset) vector. Then, to get the
 * opposite side (parallel to the (p0; p1) vector), we move both
 * endpoints by the negative (offset) vector.
 * In other words, we add/subtract the (offset) vector to/from the
 * coordinates of the line endpoints. Finally, all that remains is
 * to fill this rectangle with the specified color.
 *
 * Link to an explanatory image:
 * https://www.figma.com/design/MOGITOdwaCYQ11DAqgljlT/cub3D?node-id=53-2&
 * t=pOg82eo01UVlwuOu-0
 *
 * nx       - x component of the normal vector (n) to the (p0p1) vector;
 * ny       - y component of the normal vector (n) to the (p0p1) vector;
 * offset_x - x componenet of the normalized normal vector (n), stretched
 *			  by (line->thick / 2);
 * offset_y - y component of the normalized and stretched vector (n);
 * nlen     - length of the normal vector (n). */
void	draw_line_thick(mlx_image_t *img, t_line *line)
{
	double	nx;
	double	ny;
	double	n_len;
	int		offset_x;
	int		offset_y;

	nx = -1 * (line->p1.y - line->p0.y);
	ny = line->p1.x - line->p0.x;
	n_len = sqrt((nx * nx) + (ny * ny));
	if (n_len == 0)
		return ;
	offset_x = round((nx / n_len) * ((double)line->thick / 2.0));
	offset_y = round((ny / n_len) * ((double)line->thick / 2.0));
	draw_girdling_rect(img, line, offset_x, offset_y);
}

static void	draw_girdling_rect(mlx_image_t *img, t_line *line,
	int offset_x, int offset_y)
{
	t_coord	a;
	t_coord	b;
	t_coord	c;
	t_coord	d;

	a.x = line->p0.x + offset_x;
	a.y = line->p0.y + offset_y;
	b.x = line->p1.x + offset_x;
	b.y = line->p1.y + offset_y;
	c.x = line->p1.x - offset_x;
	c.y = line->p1.y - offset_y;
	d.x = line->p0.x - offset_x;
	d.y = line->p0.y - offset_y;
	draw_line(img, a, b, line->color);
	draw_line(img, b, c, line->color);
	draw_line(img, c, d, line->color);
	draw_line(img, d, a, line->color);
}
