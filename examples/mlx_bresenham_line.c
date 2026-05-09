/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bresenham_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:48:43 by dchernik          #+#    #+#             */
/*   Updated: 2026/05/09 20:49:35 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "MLX42.h"

#define WIN_WIDTH	256
#define WIN_HEIGHT	256

#define BR_DX	0
#define BR_DY	1
#define BR_SX	0
#define BR_SY	1

void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

/* Our graphics data: the image buffer
 * associated with the current window */
typedef struct s_graph_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_graph_data;

/* Updates accumulated error term.
 *     deltas[0] - dx;
 *     deltas[1] - dy;
 *     steps[0]  - sx;
 *     steps[1]  - sy. */
void	bresenham_update_error(t_coord *p0, int *err, int deltas[], int steps[])
{
	int	e2;

	e2 = 2 * *err;
	if (e2 >= deltas[BR_DY])
	{
		*err += deltas[BR_DY];
		p0->x += steps[BR_SX];
	}
	if (e2 <= deltas[BR_DX])
	{
		*err += deltas[BR_DX];
		p0->y += steps[BR_SY];
	}
}

/* Draws a line between two points p0 and p1 using Bresenham's algorithm.
 *     deltas[0] - dx;
 *     deltas[1] - dy;
 *     steps[0]  - sx;
 *     steps[1]  - sy. */
static void	draw_line(mlx_image_t *img, t_coord *p0, t_coord *p1, uint32_t color)
{
	int	deltas[2];
	int	steps[2];
	int	err;

	steps[BR_SX] = -1;
	steps[BR_SY] = -1;
	deltas[BR_DX] = abs(p1->x - p0->x);
	if (p0->x < p1->x)
		steps[BR_SX] = 1;
	deltas[BR_DY] = -abs(p1->y - p0->y);
	if (p0->y < p1->y)
		steps[BR_SY] = 1;
	err = deltas[BR_DX] + deltas[BR_DY];
	while (1)
	{
		mlx_put_pixel(img, p0->x, p0->y, color);
		if (p0->x == p1->x && p0->y == p1->y)
			break ;
		bresenham_update_error(p0, &err, deltas, steps);
	}
}

int	main(void)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_coord			p0;
	t_coord			p1;

	mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Bresenham's Line Algorithm", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
		ft_error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		ft_error();
	p0.x = 10;
	p0.y = 20;
	p1.x = 100;
	p1.y = 100;
	draw_line(img, &p0, &p1, 0x00FF00FF);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
