/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 08:44:11 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/27 12:51:40 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "cube.h"

void	render_floor_ceiling(t_cube *cube)
{
	int	x;
	int	y;

	y = 0;
	while (y < cube->gfx.win_height / 2)
	{
		x = 0;
		while (x < cube->gfx.win_width)
		{
			mlx_put_pixel(cube->gfx.img, x, y, cube->ceiling_color);
			++x;
		}
		++y;
	}
	while (y < cube->gfx.win_height)
	{
		x = 0;
		while (x < cube->gfx.win_width)
		{
			mlx_put_pixel(cube->gfx.img, x, y, cube->floor_color);
			++x;
		}
		++y;
	}
}

/* Returns a temporary wall color for the
 * current ray hit. Since we do not render
 * textures yet, we use two different
 * gray colors to make the 3D view easier
 * to read.
 * side == X_SIDE means that the ray hit
 * a vertical side of a map cell, while
 * side == Y_SIDE means that it hit a
 * horizontal side. Drawing one side
 * slightly darker creates a simple shading
 * effect and helps us see the wall direction
 * and check that the DDA algorithm works
 * correctly. Later, this temporary coloring
 * will be replaced by texture selection
 * depending on the wall orientation
 * LET'S JUST LEAVE IT HERE TEMPORARY
 * FOR DEBUGGING PURPOSES */
/*uint32_t	render_wall_color(int side)
{
	if (side == X_SIDE)
		return (COLOR_GRAY);
	return (COLOR_LIGHT_GRAY);
}*/
