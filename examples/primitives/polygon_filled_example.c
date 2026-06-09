/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_filled_example.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:52:31 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/08 16:23:16 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    First: build MLX42 library
		(cd ../../mlx42/ && \
		cmake -B build -DDEBUG=1 && \
		cmake --build build/ -j$(nproc --all))
	Then this:
		gcc polygon_filled_example.c \
		graphx_utils.c graphx_line.c \
		graphx_line_thick.c graphx_polygon.c \
		graphx_polygon2.c graphx_circle.c \
		../../mlx42/build/libmlx42.a \
		-O0 -g3 -ldl -lglfw -pthread -lm -lGL \
		-o polygon_filled_example
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "graphx.h"

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_polygon	poly;
	t_polygon	poly2;

	mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Drawing a filled polygon", true);
	if (!mlx)
		graphx_error();
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
		graphx_error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		graphx_error();

	polygon_init(&poly, 3);
	poly.thick = 1;
	poly.color = 0x00FF00FF;
	poly.vertices[0].x = 50;
	poly.vertices[0].y = 50;
	poly.vertices[1].x = 150;
	poly.vertices[1].y = 100;
	poly.vertices[2].x = 300;
	poly.vertices[2].y = 300;
	polygon_fill(img, &poly);
	polygon_draw(img, &poly);

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
	polygon_fill(img, &poly2);
	polygon_draw(img, &poly2);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	polygon_free(&poly);
	polygon_free(&poly2);
	return (EXIT_SUCCESS);
}
