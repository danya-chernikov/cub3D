/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:32:41 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/12 15:47:27 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "cube.h"

#include <math.h> /* For sqrt() */

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

/* Reads the current WASD keyboard state and
 * moves the player accordingly. Diagonal
 * movement is normalized so that it is not
 * faster than horizontal or vertical movement.
 * How do we normalize:
 * https://www.figma.com/design/MOGITOdwaCYQ11DAqgljlT/cub3D?
 * node-id=168-3&t=cIe9W1KPA9g55vKf-0 */
void	player_handle_input(t_cube *cube)
{
	double	dx;
	double	dy;
	double	len;

	dx = 0;
	dy = 0;
	if (mlx_is_key_down(cube->gfx.mlx, MLX_KEY_W))
		dy -= 1;
	if (mlx_is_key_down(cube->gfx.mlx, MLX_KEY_S))
		dy += 1;
	if (mlx_is_key_down(cube->gfx.mlx, MLX_KEY_A))
		dx -= 1;
	if (mlx_is_key_down(cube->gfx.mlx, MLX_KEY_D))
		dx += 1;
	len = sqrt(dx * dx + dy * dy);
	if (len > 0)
		player_move(cube, (dx / len) * cube->player.speed,
			(dy / len) * cube->player.speed);
}
