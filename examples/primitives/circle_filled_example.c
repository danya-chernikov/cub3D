/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_filled_example.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:02:17 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/08 16:22:50 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    First: build MLX42 library
		(cd ../../mlx42/ && \
		cmake -B build -DDEBUG=1 && \
		cmake --build build/ -j$(nproc --all))
	Then this:
		gcc circle_filled_example.c \
		graphx_utils.c graphx_line.c \
		graphx_line_thick.c graphx_polygon.c \
		graphx_polygon2.c graphx_circle.c \
		../../mlx42/build/libmlx42.a \
		-O0 -g3 -ldl -lglfw -pthread -lm -lGL \
		-o circle_filled_example
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

	mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Drawing a circle", true);
	if (!mlx)
		graphx_error();
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
		graphx_error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		graphx_error();

	circle_filled_draw(img, (t_coord){150, 150}, 50, 0x00FF00FF);
	circle_filled_draw(img, (t_coord){300, 300}, 100, 0xFFFF00FF);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
