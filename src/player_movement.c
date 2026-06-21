/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 01:13:03 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/21 01:18:13 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "cube.h"

/* Moves the player by the given delta if the movement
 * does not cause a collision with a wall. The x and
 * y axes are checked separately to allow smooth sliding
 * along walls */
void	player_move(t_cube *cube, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = cube->player.pos.x + dx;
	new_y = cube->player.pos.y + dy;
	if (!player_hits_wall(cube, new_x, cube->player.pos.y))
		cube->player.pos.x = new_x;
	if (!player_hits_wall(cube, cube->player.pos.x, new_y))
		cube->player.pos.y = new_y;
}
