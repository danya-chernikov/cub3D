/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphx_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 19:58:47 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/10 20:03:19 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphx.h"
#include "cube.h"

void	graphx_resize_hook(int32_t width, int32_t height, void *param)
{
	t_cube	*cube;

	cube = (t_cube *)param;
	if (width <= 0 || height <= 0)
		return ;
	cube->gfx.win_width = width;
	cube->gfx.win_height = height;
	if (!mlx_resize_image(cube->gfx.img, width, height))
		graphx_error();
}
