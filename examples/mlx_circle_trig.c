/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_circle_dumb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 12:51:14 by dchernik          #+#    #+#             */
/*   Updated: 2026/05/14 12:54:05 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "MLX42.h"

#define WIN_WIDTH	512
#define WIN_HEIGHT	512

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	draw_circle(mlx_image_t *img, t_coord *center, int radius, uint32_t color)
{
	int		x;
	int		y;
	int		angle;
	float	radians;

	angle = 0;
	while (angle < 360)
	{
		radians = (angle * M_PI) / 180;
		x = center->x + radius * cos(radians);
		y = center->y + radius * sin(radians);
		mlx_put_pixel(img, x, y, color);
		++angle;
	}
}

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_coord		center;

	mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Attempt to draw a circle", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
		ft_error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		ft_error();
	center.x = WIN_WIDTH / 2;
	center.y = WIN_HEIGHT / 2;
	draw_circle(img, &center, 100, 0xFF0000FF);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
