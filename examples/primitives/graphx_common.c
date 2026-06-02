/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphx_common.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:11:47 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/02 17:52:19 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphx.h"

#include <stdio.h>
#include <stdlib.h>

void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	put_pixel_safe(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x < 0 || y < 0)
		return ;
	if ((uint32_t)x >= img->width || (uint32_t)y >= img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}
