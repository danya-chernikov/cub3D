/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:53:27 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/09 18:07:25 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/* Finds the player's spawn position in the map */
void	player_init(t_cube *cube)
{
	int	x;
	int	y;

	y = 0;
	while (y < cube->map_height)
	{
		x = 0;
		while (cube->map[y][x])
		{
			if (is_player_spawn(cube->map[y][x]))
			{
				set_player_spawn(cube, x, y);
				return ;
			}
			++x;
		}
		++y;
	}
}

int	is_player_spawn(u_char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

/* Sets the player position to the center of the
 * spawn cell. After that, the spawn character is
 * replaced with '0', because this map cell becomes
 * a normal walkable floor */
void	set_player_spawn(t_cube *cube, int x, int y)
{
	cube->player.pos.x = x + 0.5;
	cube->player.pos.y = y + 0.5;
	cube->player.collision_radius = PLAYER_COL_RADIUS;
	cube->player.speed = PLAYER_SPEED;
	cube->map[y][x] = '0';
}
