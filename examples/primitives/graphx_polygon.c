/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphx_polygon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:11:55 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/05 13:18:17 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphx.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int	polygon_init(t_polygon *poly, int vert_num)
{
	if (vert_num < 3)
		return (COMMON_FAILURE);
	poly->vert_num = vert_num;
	poly->vertices = malloc(vert_num * sizeof(t_coord));
	if (!poly->vertices)
	{
		perror("malloc");
		return (COMMON_FAILURE);
	}
	return (COMMON_SUCCESS);
}

void	polygon_free(t_polygon *poly)
{
	free(poly->vertices);
}

void	polygon_draw(mlx_image_t *img, t_polygon *poly)
{
	int	vi;
	int	next;

	vi = 0;
	while (vi < poly->vert_num)
	{
		next = (vi + 1) % poly->vert_num;
		draw_line(img, poly->vertices[vi], poly->vertices[next], poly->color);
		++vi;
	}
}

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
