/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphx_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:11:53 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/03 20:36:20 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphx.h"

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

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
void	bresenham_update_error(t_coord *p0, int *err,
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

