/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphx_circle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:11:41 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/05 15:06:53 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphx.h"

/* Used by circle_draw() */
static void	put_circle_points(mlx_image_t *img, t_coord c,
	t_coord p, uint32_t color);

/* Used by circle_filled_draw() */
static void	put_circle_lines(mlx_image_t *img, t_coord c,
	t_coord p, uint32_t color);

/* Basic midpoint circle algorithm implementation.
 * Here we calculate the points of one octant of the
 * circumference and then reflect each point onto the
 * other seven symmetrical positions */
void	circle_draw(mlx_image_t *img, t_coord center,
	int radius, uint32_t color)
{
	t_coord		p;
	int			err;

	if (radius < 0)
		return ;
	p.x = 0;
	p.y = radius;
	err = 3 - 2 * radius;
	while (p.x <= p.y)
	{
		put_circle_points(img, center, p, color);
		if (err <= 0)
			err += 4 * p.x + 6;
		else
		{
			err += 4 * (p.x - p.y) + 10;
			--p.y;
		}
		++p.x;
	}
}

void	circle_filled_draw(mlx_image_t *img, t_coord center,
	int radius, uint32_t color)
{

	t_coord		p;
	int			err;

	if (radius < 0)
		return ;
	p.x = 0;
	p.y = radius;
	err = 3 - 2 * radius;
	while (p.x <= p.y)
	{
		put_circle_lines(img, center, p, color);
		if (err <= 0)
			err += 4 * p.x + 6;
		else
		{
			err += 4 * (p.x - p.y) + 10;
			--p.y;
		}
		++p.x;
	}
}

/* Mirrors one calculated circle point into all 8 octants
 * and plots the resulting symmetric points */
static void	put_circle_points(mlx_image_t *img, t_coord c,
	t_coord p, uint32_t color)
{
	put_pixel_safe(img, c.x + p.x, c.y + p.y, color);
	put_pixel_safe(img, c.x - p.x, c.y + p.y, color);
	put_pixel_safe(img, c.x + p.x, c.y - p.y, color);
	put_pixel_safe(img, c.x - p.x, c.y - p.y, color);
	put_pixel_safe(img, c.x + p.y, c.y + p.x, color);
	put_pixel_safe(img, c.x - p.y, c.y + p.x, color);
	put_pixel_safe(img, c.x + p.y, c.y - p.x, color);
	put_pixel_safe(img, c.x - p.y, c.y - p.x, color);
}

/* The only difference between this function and
 * put_circle_points() is that here, instead of
 * plotting points, we draw horizontal lines between
 * symmetric points of the circle.
 *     dx - delta x */
static void	put_circle_lines(mlx_image_t *img, t_coord c,
	t_coord p, uint32_t color)
{
	t_pair_int	dx;

	dx.first = c.x - p.x;
	dx.second = c.x + p.x;
	draw_hline(img, &dx, c.y + p.y, color);
	dx.first = c.x - p.x;
	dx.second = c.x + p.x;
	draw_hline(img, &dx, c.y - p.y, color);
	dx.first = c.x - p.y;
	dx.second = c.x + p.y;
	draw_hline(img, &dx, c.y + p.x, color);
	dx.first = c.x - p.y;
	dx.second = c.x + p.y;
	draw_hline(img, &dx, c.y - p.x, color);
}
