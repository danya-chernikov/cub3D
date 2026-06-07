/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:59:46 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/07 19:54:38 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cube.h"
#include "error.h"
#include "parser.h"

#include <stdlib.h> /* for free() */
#include <stdio.h> // for printf testing parsing

int main(int ac, char **av)
{
	t_cube	*cube;

	if (ac != 2)
	{
		print_error("Invalid number of arguments");
		return (EXIT_FAILURE);
	}
	cube = ft_calloc(1, sizeof(*cube));
	if (!cube)
	{
		print_error("Memory allocation failed");
		return (EXIT_FAILURE);
	}
	if (!parse_cub_file(av[1], cube))
	{
		free_cube(cube);
		return (EXIT_FAILURE);
	}

	printf("Map %s is valid\n", av[1]);

	cube->gfx.mlx = mlx.init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
	if (!cube->gfx.mlx)
		ft_error();

	cube->gfx.img = mlx_new_image(cube->gfx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cube->gfx.img)
		ft_error();

	if (mlx_image_to_window(cube->gfx.mlx, cube->gfx.img, 0, 0) < 0)
		ft_error();

	mlx_loop_hook(cube->gfx.mlx, game_loop, cube);
	mlx_loop(cube->gfx.mlx);

	mlx_terminate(cube->gfx.mlx);
	free_cube(cube);
	return (EXIT_SUCCESS);
}
