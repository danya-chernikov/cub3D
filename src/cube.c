/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:19:23 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/08 16:08:36 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "minimap.h"

#include <stdio.h>
#include <stdbool.h>

int	graphx_init(t_cube *cube)
{
	cube->gfx.mlx = mlx.init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
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
	clear_image(cube->gfx.img, 0x202020FF);
	//player_handle_input(cube);
	minimap_draw(cube->gfx.img, cube);
}

/* Fills the entire image with one color. This isused
 * to clear the previous frame before drawing the next
 * one. Obviously, we cannot go outside the window area
 * here, so we can simply use mlx_put_pixel() */
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
