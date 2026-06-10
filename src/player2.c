#include "cube.h"

#include <math.h>

/* Moves the player by the given delta */
void	player_move(t_cube *cube, double dx, double dy)
{
	cube->player.pos.x += dx;
	cube->player.pos.y += dy;
}

/* Reads the current WASD keyboard state and
 * moves the player accordingly. Diagonal
 * movement is normalized so that it is not
 * faster than horizontal or vertical movement */
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
