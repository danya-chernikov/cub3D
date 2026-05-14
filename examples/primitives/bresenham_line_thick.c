/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_thick.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:48:43 by dchernik          #+#    #+#             */
/*   Updated: 2026/05/14 17:58:51 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "MLX42.h"

#define WIN_WIDTH	512
#define WIN_HEIGHT	512

#define BR_DX	0
#define BR_DY	1
#define BR_SX	0
#define BR_SY	1

/* Our graphics data: the image buffer
 * associated with the current window */
typedef struct s_graph_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_graph_data;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

/* think - line's thinkness in pixels */
typedef struct s_line
{
	t_coord		p0;
	t_coord		p1;
	uint32_t	color;
	int			thick;
}	t_line;

void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

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
void	draw_line(mlx_image_t *img, t_coord *p0, t_coord *p1, uint32_t color)
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

void	draw_line_thick(mlx_image_t *img, t_line *line)
{
	int		x0i;
	int		x1i;
	t_coord	dp0;
	t_coord	dp1;

	x0i = line->p0.x - line->thick / 2;
	x1i = line->p1.x - line->thick / 2;
	while (x0i < line->p0.x + line->thick / 2)
	{
		dp0.x = x0i;
		dp0.y = line->p0.y;
		dp1.x = x1i;
		dp1.y = line->p1.y;
		draw_line(img, &dp0, &dp1, line->color);
		++x0i;
		++x1i;
	}
}

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

	line.p0.x = 10;
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
	draw_line_thick(img, &line2);

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
