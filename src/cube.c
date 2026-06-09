/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:19:23 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/08 21:49:50 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cube.h"
#include "minimap.h"
#include "parser.h"
#include "error.h"

#include <stdio.h>
#include <stdbool.h>

t_cube	*parser_init(int argc, char **argv)
{
	t_cube	*cube;

	if (argc != 2)
	{
		print_error("Invalid number of arguments");
		return (NULL);
	}
	cube = ft_calloc(1, sizeof(*cube));
	if (!cube)
	{
		print_error("Memory allocation failed");
		return (NULL);
	}
	if (!parse_cub_file(argv[1], cube))
	{
		free_cube(cube);
		return (NULL);
	}
#if DEBUG_LVL == 1
	printf("Map %s is valid\n", argv[1]);
#endif
	return (cube);
}

int	graphx_init(t_cube *cube)
{
	cube->gfx.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
	if (!cube->gfx.mlx)
		return (COMMON_FAILURE);
	cube->gfx.img = mlx_new_image(cube->gfx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cube->gfx.img)
		return (COMMON_FAILURE);
	if (mlx_image_to_window(cube->gfx.mlx, cube->gfx.img, 0, 0) < 0)
		return (COMMON_FAILURE);
	return (COMMON_SUCCESS);
}

void	game_loop(void *param)
{
	t_cube	*cube;

	cube = param;
	clear_image(cube->gfx.img, COLOR_BLUISH);
	//player_handle_input(cube);
	minimap_draw(cube->gfx.img, cube);
}

/* Fills the entire image with one color. This isused
 * to clear the previous frame before drawing the next
 * one. Obviously, we cannot go outside the window area
 * here, so we can simply use mlx_put_pixel()
 *
 * BETTER TO MOVE THIS FUNCTION IN ANOTHER PLACE! */
void	clear_image(mlx_image_t *img, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, color);
			++x;
		}
		++y;
	}
}
