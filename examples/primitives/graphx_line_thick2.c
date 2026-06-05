/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphx_line_thick2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 20:39:40 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/05 10:45:24 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphx.h"

#include <math.h>
#include <stdlib.h>

/* Finds and returns the minimum y coordinate
 * among all vertices of the polygon `poly` */
int	polygon_min_y(t_polygon *poly)
{
	int	i;
	int	min_y;

	i = 1;
	min_y = poly->vertices[0].y;
	while (i < poly->vert_num)
	{
		if (poly->vertices[i].y < min_y)
			min_y = poly->vertices[i].y;
		++i;
	}
	return (min_y);
}

/* Finds and returns the maximum y coordinate
 * among all vertices of the polygon `poly` */
int	polygon_max_y(t_polygon *poly)
{
	int	i;
	int	max_y;

	i = 1;
	max_y = poly->vertices[0].y;
	while (i < poly->vert_num)
	{
		if (poly->vertices[i].y > max_y)
			max_y = poly->vertices[i].y;
		++i;
	}
	return (max_y);
}

int	collect_intersections(t_polygon *poly, int y, double *x_intersections)
{
	int	i;
	int	next;
	int	count;

	i = 0;
	count = 0;
	while (i < poly->vert_num)
	{
		next = (i + 1) % poly->vert_num;
		if (edge_crosses_y(poly->vertices[i], poly->vertices[next], y))
		{
			x_intersections[count] =
				edge_x_at_y(poly->vertices[i], poly->vertices[next], y);
			++count;
		}
		++i;
	}
	return (count);
}

void	fill_polygon(mlx_image_t *img, t_polygon *poly)
{
	double		*x_intersections;
	int			y;
	int			count;
	int			i;
	t_pair_int	x;

	x_intersections = malloc(poly->vert_num * sizeof(double));
	if (!x_intersections)
		return ;
	y = polygon_min_y(poly);
	while (y <= polygon_max_y(poly))
	{
		count = collect_intersections(poly, y, x_intersections);
		quick_sort_doubles(x_intersections, 0, count - 1);
		i = 0;
		while (i + 1 < count)
		{
			x.first = (int)ceil(x_intersections[i]);
			x.second = (int)floor(x_intersections[i + 1]);
			draw_hline(img, &x, y, poly->color);
			i += 2;
		}
		++y;
	}
	free(x_intersections);
}
