/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:59:46 by dchernik          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/06/06 19:52:52 by dchernik         ###   ########.fr       */
=======
/*   Updated: 2026/06/05 17:31:31 by adeestev         ###   ########.fr       */
>>>>>>> main
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


	// Map and/or player initialization
	cube->map_width = 33;
	cube->map_height = 14;
	cube->map = malloc(cube->map_height * sizeof (char *));
	if (!cube->map)
	{
		perror("malloc");
		return (EXIT_FAILURE);
	}
	for (int i = 0; i < cube->map_height; ++i)
	{
		cube->map[i] = malloc(cube->map_width * sizeof (char));
		if (!cube->map[i])
		{
			for (int j = i - 1; j >= 0; --j)
				free(cube->map[j]);
			free(cube->map);
			perror("malloc");
			return (EXIT_FAILURE);
		}
	}

	map->cube[0]  = "        1111111111111111111111111";
	map->cube[1]  = "        1000000000110000000000001";
	map->cube[2]  = "        1011000001110000000000001";
	map->cube[3]  = "		 1001000000000000000000001";
	map->cube[4]  = "111111111011000001110000000000001";
	map->cube[5]  = "100000000011000001110111111111111";
	map->cube[6]  = "11110111111111011100000010001    ";
	map->cube[7]  = "11110111111111011101010010001    ";
	map->cube[8]  = "11000000110101011100000010001    ";
	map->cube[9]  = "10000000000000001100000010001    ";
	map->cube[10] = "10000000000000001101010010001    ";
	map->cube[11] = "11000001110101011111011110N0111  ";
	map->cube[12] = "11110111 1110101 101111010001    ";
	map->cube[13] = "11111111 1111111 111111111111    ";

	for (int i = 0; i < cube->map_height; ++i)
		free(cube->map[i]);
	free(cube->map);

	// ...
	// Rendering...

	printf("Map %s is valid\n", av[1]);  // testing parsing



	free_cube(cube);
	return (EXIT_SUCCESS);
}
