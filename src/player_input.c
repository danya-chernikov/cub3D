/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 01:13:09 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/25 19:50:40 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "cube.h"

#include <math.h> /* For sqrt() */

/* Reads the current keyboard state and updates
 * the player. Arrow keys rotate the view, while
 * WASD moves the player relative to the current
 * viewing direction. Movement is multiplied by
 * `delta_time` so the player moves at the same
 * speed even if FPS changes. Diagonal movement
 * is normalized so that it is not faster than
 * horizontal or vertical movement.
 *     move - a temporary vector of the player's
 *			  desired movement for the current frame.
 * How do we normalize:
 * https://www.figma.com/design/MOGITOdwaCYQ11DAqgljlT/cub3D?
 * node-id=168-3&t=cIe9W1KPA9g55vKf-0 */
void	player_handle_input(t_cube *cube)
{
	t_dcoord	dir;
	t_dcoord	right;
	t_dcoord	move;
	double		len;

	player_update_rotation(cube);
	dir = player_dir(cube);
	right = player_right(dir);
	move.x = 0;
	move.y = 0;
	player_add_move(cube, &move, dir, right);
	len = sqrt(move.x * move.x + move.y * move.y);
	if (len > 0)
	{
		player_move(cube,
			(move.x / len) * cube->player.speed * cube->delta_time,
			(move.y / len) * cube->player.speed * cube->delta_time);
	}
}

/* Updates the player's viewing angle.
 * Rotation speed is measured in radians
 * per second so similarly it's multiplied
 * by `delta_time` */
void	player_update_rotation(t_cube *cube)
{
	if (mlx_is_key_down(cube->gfx.mlx, MLX_KEY_LEFT))
		cube->player.angle -= PLAYER_ROT_SPEED * cube->delta_time;
	if (mlx_is_key_down(cube->gfx.mlx, MLX_KEY_RIGHT))
		cube->player.angle += PLAYER_ROT_SPEED * cube->delta_time;
}

/* Returns the player's forward direction
 * vector. The vector is computed from
 * the player's current angle. In our
 * coordinate system, x grows to the right
 * and y grows down, so angle 0 points
 * east and PI / 2 points south */
t_dcoord	player_dir(t_cube *cube)
{
	t_dcoord	dir;

	dir.x = cos(cube->player.angle);
	dir.y = sin(cube->player.angle);
	return (dir);
}

/* Returns the vector pointing to the
 * player's right side. This vector is
 * perpendicular to the forward direction
 * and is used for strafing with A and D */
t_dcoord	player_right(t_dcoord dir)
{
	t_dcoord	right;

	right.x = -dir.y;
	right.y = dir.x;
	return (right);
}

/* Adds movement input to the given move vector.
 * W and S move forward and backward relative to
 * the player's direction, while A and D move left
 * and right using the perpendicular right vector */
void	player_add_move(t_cube *cube, t_dcoord *move,
	t_dcoord dir, t_dcoord right)
{
	if (mlx_is_key_down(cube->gfx.mlx, MLX_KEY_W))
	{
		move->x += dir.x;
		move->y += dir.y;
	}
	if (mlx_is_key_down(cube->gfx.mlx, MLX_KEY_S))
	{
		move->x -= dir.x;
		move->y -= dir.y;
	}
	if (mlx_is_key_down(cube->gfx.mlx, MLX_KEY_D))
	{
		move->x += right.x;
		move->y += right.y;
	}
	if (mlx_is_key_down(cube->gfx.mlx, MLX_KEY_A))
	{
		move->x -= right.x;
		move->y -= right.y;
	}
}
