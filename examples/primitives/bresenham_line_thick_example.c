/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_thick_example.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:33:03 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/23 15:17:56 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    First: build MLX42 library
		(cd ../../mlx42/ && \
		cmake -B build -DDEBUG=1 && \
		cmake --build build/ -j$(nproc --all))
	Then this:
		gcc bresenham_line_thick_example.c \
		graphx_utils.c graphx_line.c \
		graphx_line_thick.c graphx_polygon.c \
		graphx_polygon2.c graphx_circle.c \
		../../mlx42/build/libmlx42.a \
		-O0 -g3 -ldl -lglfw -pthread -lm -lGL \
		-o bresenham_line_thick_example
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "graphx.h"

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_line		line;
	t_line		line2;

	mlx = mlx_init(512, 512,
		"Bresenham's line algorithm with sickness", true);
	if (!mlx)
		graphx_error();
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
		graphx_error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		graphx_error();

	draw_line_thick(img,
		&(t_line){(t_coord){10, 20}, (t_coord){100, 100}, 0x00FF00FF, 10});

	draw_line_thick(img,
		&(t_line){(t_coord){80, 20}, (t_coord){400, 120}, 0x0000FFFF, 1});

	draw_line_thick(img,
		&(t_line){(t_coord){256, 256}, (t_coord){480, 256}, 0xFF00FFFF, 5});

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
