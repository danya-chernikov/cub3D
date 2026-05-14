#include "MLX42.h"
#include <stdlib.h>
#include <string.h>

// Bytes Per Pixel
#define BPP	sizeof(int32_t)
#define WIDTH	256
#define HEIGHT	256

int32_t	main(void)
{
	// Init mlx with a canvas size of WIDTHxHEIGHT and
	// the ability to resize the window
	mlx_t	*mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);

	// Create a 128x128 image
	mlx_image_t	*img = mlx_new_image(mlx, 128, 128);

	// Set the channels of each pixel in our image to the
	// maximum byte value of 0xFF
	memset(img->pixels, 0xFF, img->width * img->height * BPP);
	
	// Draw the image at coordinate (25, 25)
	mlx_image_to_window(mlx, img, 25, 25);

	// Run the main loop and terminate on quit
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
