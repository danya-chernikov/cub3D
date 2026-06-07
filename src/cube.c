/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:19:23 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/07 20:17:12 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

#include <stdio.h>

void	game_loop(void *param)
{
	t_cube	*cube;

	cube = param;
	clear_image(cube->gfx.img, 0x202020FF);
	player_handle_input(cube);
	minimap_draw(cube->gfx.img, cube);
}

void	player_init(t_cube *cube)
{

}

void		minimap_init(t_cube *cube)
{

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
