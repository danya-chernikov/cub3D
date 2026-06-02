/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_thick.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:48:43 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/02 17:58:11 by dchernik         ###   ########.fr       */
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
