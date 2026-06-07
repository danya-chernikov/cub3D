/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:59:46 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/05 17:31:31 by adeestev         ###   ########.fr       */
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
	// ...
	// Rendering...

	printf("Map %s is valid\n", av[1]);  // testing parsing



	free_cube(cube);
	return (EXIT_SUCCESS);
}
