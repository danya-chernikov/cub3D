/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:59:46 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/08 21:22:17 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "parser.h"

#include <stdlib.h> /* For free() */
#include <stdio.h> /* For printf testing parsing */

int main(int argc, char **argv)
{
	t_cube	*cube;

	cube = parser_init(argc, argv);
	if (!cube)
		exit(EXIT_FAILURE);
	player_init(cube);
	minimap_init(cube, (t_coord){MINIMAP_POS_X, MINIMAP_POS_Y});
	if (!graphx_init(cube))
		graphx_error();
	mlx_loop_hook(cube->gfx.mlx, game_loop, cube);
	mlx_loop(cube->gfx.mlx);
	mlx_terminate(cube->gfx.mlx);
	free_cube(cube);
	return (EXIT_SUCCESS);
}
