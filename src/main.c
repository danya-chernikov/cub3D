/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:59:46 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/08 15:54:35 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cube.h"
#include "error.h"
#include "parser.h"

#include <stdlib.h> /* for free() */
#include <stdio.h> /* for printf testing parsing */

/* The player_init() will never fail because,
 * after successfully passing the parsing
 * stage, the existence of a player on the
 * map is guaranteed. However, we still check
 * for an erroneous result just to keep the
 * code unified and consistent */
int main(int ac, char **av)
{
	t_cube	*cube;

	if (ac != 2)
	{
		print_error("Invalid number of arguments");
		exit (EXIT_FAILURE);
	}
	cube = ft_calloc(1, sizeof(*cube));
	if (!cube)
	{
		print_error("Memory allocation failed");
		exit (EXIT_FAILURE);
	}
	if (!parse_cub_file(av[1], cube))
	{
		free_cube(cube);
		exit (EXIT_FAILURE);
	}
	printf("Map %s is valid\n", av[1]);
	if (!player_init(cube))
	{
		free_cube(cube);
		exit (EXIT_FAILURE);
	}
	minimap_init(cube, {20, 20});
	if (!graphx_init(cube))
		mlx_error();
	mlx_loop_hook(cube->gfx.mlx, game_loop, cube);
	mlx_loop(cube->gfx.mlx);
	mlx_terminate(cube->gfx.mlx);
	free_cube(cube);
	return (EXIT_SUCCESS);
}
