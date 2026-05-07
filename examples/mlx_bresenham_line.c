#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "MLX42.h"

#define WIN_WIDTH	256
#define WIN_HEIGHT	256

static void	ft_error(void)
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

static void	draw_line(mlx_image_t *img, t_coord *p0, t_coord *p1, uint32_t color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;

	sx = -1;
	sy = -1;
	dx = abs(p1->x - p0->x);
	if (p0->x < p1->x)
		sx = 1;
	dy = abs(p1->y - p0->y);
	if (p0->y < p1->y)
		sy = 1;
	err = dx + dy;
	while (1)
	{
		mlx_put_pixel(img, p0->x, p0->y, color);
		if (p0->x == p1->x && p0->y == p1->y)
			break ;
		if (2 * err >= dy)
		{
			err += dy;
			p0->x += sx;
		}
		if (2 * err <= dx)
		{
			err += dx;
			p0->y += sy;
		}
	}
}

int	main(void)
{
	mlx_t			*mlx;
	mlx_image_t		*img;

	mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Bresenham's Line Algorithm", true);
	if (!mlx)
		ft_error();

	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img)
		ft_error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		ft_error();

	draw_line(img, &(t_coord){10, 20}, &(t_coord){100, 100}, 0x00FF00FF);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

