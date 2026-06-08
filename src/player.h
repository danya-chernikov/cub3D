#ifndef PLAYER_H
# define PLAYER_H

# include "libft.h"
# include "graphx.h" /* For t_dcoord */

# define PLAYER_RADIUS	5 /* in px */

typedef struct s_cube	t_cube;

/* Stores the player's position in world coordinates.
 * One map cell is treated as 1.0 unit, so the player
 * can stand between cells, not only exactly inside
 * one cell.
 *     pos				- player's position in world coordinates,
 *						  measured in map-cell units;
 *     collision_radius - player's physical radius on the minimap,
 *						  measured in map-cell units. */
typedef struct s_player
{
	t_dcoord	pos;	
	double		collision_radius;
	double		speed;
}	t_player;

/* player.c */
void	player_init(t_cube *cube);
int		is_player_spawn(u_char c);
void	set_player_spawn(t_cube *cube, int x, int y);

#endif
