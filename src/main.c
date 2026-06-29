/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:59:46 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/29 03:57:48 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* GitHub link: https://github.com/danya-chernikov/cub3D */
#include "cube.h"
#include "parser.h"

static void	graphx_destroy(t_cube *cube)
{
	if (!cube)
		return ;
	if (cube->gfx.mlx)
	{
		mlx_terminate(cube->gfx.mlx);
		cube->gfx.mlx = NULL;
		cube->gfx.img = NULL;
	}
}

static void	cleanup(t_cube *cube)
{
	graphx_error();
	graphx_destroy(cube);
	free_cube(cube);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_cube	*cube;
	int		status;

	status = EXIT_SUCCESS;
	cube = parser_init(argc, argv);
	if (!cube)
		exit(EXIT_FAILURE);
	player_init(cube);
	if (!textures_load(cube))
	{
		free_cube(cube);
		exit(EXIT_FAILURE);
	}
	minimap_init(cube, (t_coord){MINIMAP_POS_X, MINIMAP_POS_Y});
	if (!graphx_init(cube))
		cleanup(cube);
	mlx_resize_hook(cube->gfx.mlx, graphx_resize_hook, cube);
	mlx_loop_hook(cube->gfx.mlx, game_loop, cube);
	mlx_loop(cube->gfx.mlx);
	if (cube->fatal_error)
		status = EXIT_FAILURE;
	graphx_destroy(cube);
	free_cube(cube);
	return (status);
}
