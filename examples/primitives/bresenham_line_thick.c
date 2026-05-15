/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_thick.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:48:43 by dchernik          #+#    #+#             */
/*   Updated: 2026/05/15 19:38:07 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "graphx.h"

#define WIN_WIDTH	512
#define WIN_HEIGHT	512

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_line		line;
	t_line		line2;

	mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT,
		"Bresenham's line algorithm with sickness", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
		ft_error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		ft_error();

	/*line.p0.x = 10;
	line.p0.y = 20;
	line.p1.x = 100;
	line.p1.y = 100;
	line.color = 0x00FF00FF;
	line.thick = 5;
	draw_line_thick(img, &line);

	line2.p0.x = 80;
	line2.p0.y = 20;
	line2.p1.x = 400;
	line2.p1.y = 120;
	line2.color = 0x0000FFFF;
	line2.thick = 10;
	draw_line_thick(img, &line2);*/

	line2.p0.x = 80;
	line2.p0.y = 20;
	line2.p1.x = 400;
	line2.p1.y = 120;
	line2.color = 0x0000FFFF;
	line2.thick = 10;
	draw_line_thick(img, &(t_line){(t_coord){256, 256}, (t_coord){480, 256}, 0xFF00FFFF, 1});
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
