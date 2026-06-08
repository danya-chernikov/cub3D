/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_example.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:45:54 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/08 16:23:28 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    First: build MLX42 library
		(cd ../../mlx42/ && \
		cmake -B build -DDEBUG=1 && \
		cmake --build build/ -j$(nproc --all))
	Then this:
		gcc bresenham_line_example.c \
		graphx_utils.c graphx_line.c \
		graphx_line_thick.c graphx_polygon.c \
		graphx_polygon2.c graphx_circle.c \
		../../mlx42/build/libmlx42.a \
		-O0 -g3 -ldl -lglfw -pthread -lm -lGL \
		-o bresenham_line_example
*/

#include <stdlib.h>

#include "graphx.h"

int	main(void)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_coord			p0;
	t_coord			p1;

	mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Bresenham's Line Algorithm", true);
	if (!mlx)
		graphx_error();
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
		graphx_error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		graphx_error();
	p0.x = 10;
	p0.y = 20;
	p1.x = 100;
	p1.y = 100;
	draw_line(img, p0, p1, 0x00FF00FF);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
