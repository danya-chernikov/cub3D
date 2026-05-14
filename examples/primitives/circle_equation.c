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

/* Checks whether the coordinates of
 * a plotted pixel are not outside
 * the window borders */
void	put_pixel_safe(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x < 0 || y < 0)
		return ;
	if (x >= (int)img->width || y >= (int)img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

/* From standard circle equation
 * (x - x0)^2 + (y - y0)^2 = R^2
 * we derived y
 * y = sqrt(R^2 - (x - x0)^2) + y0
 * y = -sqrt(R^2 - (x - x0)^2) + y0
 * And then just plot pixels for 0 to WIN_WIDTH
 * */
void	draw_circle(mlx_image_t *img, t_coord *center, int radius, uint32_t color)
{
	int	x;
	int	y;
	int	dx;
	int	inside;

	x = center->x - radius;
	while (x <= center->x + radius)
	{
		dx = x - center->x;
		inside = radius * radius - dx * dx;
		y = (int)sqrt(inside) + center->y;
		put_pixel_safe(img, x, y, color);
		y = -(int)sqrt(inside) + center->y;
		mlx_put_pixel(img, x, y, color);
		++x;
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
