/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_example.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:48:43 by dchernik          #+#    #+#             */
/*   Updated: 2026/05/14 19:06:15 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "graphx.h"

#define WIN_WIDTH	512
#define WIN_HEIGHT	512

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_polygon	poly;
	t_polygon	poly2;

	mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Drawing a polygon", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
		ft_error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		ft_error();

	polygon_init(&poly, 3);
	poly.thick = 1;
	poly.color = 0x00FF00FF;
	poly.vertices[0].x = 50;
	poly.vertices[0].y = 50;
	poly.vertices[1].x = 150;
	poly.vertices[1].y = 100;
	poly.vertices[2].x = 300;
	poly.vertices[2].y = 300;
	draw_polygon(img, &poly);

	polygon_init(&poly2, 4);
	poly2.thick = 1;
	poly2.color = 0x00FFFFFF;
	poly2.vertices[0].x = 100;
	poly2.vertices[0].y = 100;
	poly2.vertices[1].x = 400;
	poly2.vertices[1].y = 100;
	poly2.vertices[2].x = 400;
	poly2.vertices[2].y = 300;
	poly2.vertices[3].x = 100;
	poly2.vertices[3].y = 300;
	draw_polygon(img, &poly2);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	polygon_free(&poly);
	polygon_free(&poly2);
	return (EXIT_SUCCESS);
}
