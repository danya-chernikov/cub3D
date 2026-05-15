/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphx_polygon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:11:55 by dchernik          #+#    #+#             */
/*   Updated: 2026/05/15 19:11:58 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphx.h"

#include <stdlib.h>

int	polygon_init(t_polygon *poly, int vert_num)
{
	if (vert_num < 3)
		return (COMMON_FAILURE);
	poly->vert_num = vert_num;
	poly->vertices = malloc(vert_num * sizeof(t_coord));
	if (!poly->vertices)
		return (COMMON_FAILURE);
	return (COMMON_SUCCESS);
}

void	polygon_free(t_polygon *poly)
{
	free(poly->vertices);
}

void	draw_polygon(mlx_image_t *img, t_polygon *poly)
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
