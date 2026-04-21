/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw_win.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:57:59 by dchernik          #+#    #+#             */
/*   Updated: 2026/04/21 18:58:00 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <stdlib.h>

int main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(800, 600, "cub3D", true);
	if (!mlx)
		return (EXIT_FAILURE);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
