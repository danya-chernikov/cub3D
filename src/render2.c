/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 08:44:11 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/27 18:44:18 by dchernik         ###   ########.fr       */
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
