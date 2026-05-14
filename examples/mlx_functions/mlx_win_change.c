#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "MLX42.h"

#define WIN_WIDTH	256
#define WIN_HEIGHT	256

/* Exit the program as failure */
static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

/* Print the window width and height */
static void	ft_hook(void *param)
{
	const mlx_t	*mlx = param;
	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	// MLX allows you to define its core behaviour before startup
	// Tells mlx42 to start the window maximized
	mlx_set_setting(MLX_MAXIMIZED, true);
	// Initialize MLX42 and create the main window handle
	mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Change Window Size", true);
	// The fourth parameter 'true' means we request resizing/high-DPI behaviour
	if (!mlx)
		ft_error();

	// Do stuff

	// This creates 256x256 image buffer
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	// This displays that image in the window at position (0, 0)
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Even after the image is being displayed, we can still modify the buffer
	// This changes the pixel at the top-left corner of the image
	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

	// Register a hook and pass mlx as an optional param
	// NOTE: Do this before calling mlx_loop!
	// In other words, here we register ft_hook() as a
	// function to be called repeatedly during the loop
	mlx_loop_hook(mlx, ft_hook, mlx);
	// This starts the main event/render loop
	mlx_loop(mlx);
	// Frees mlx resources after the loop ends
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
