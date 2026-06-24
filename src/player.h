/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:32:49 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/24 16:01:13 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "libft.h"
# include "graphx.h" /* For t_dcoord */

# define PLAYER_RADIUS		5				/* In px */
# define PLAYER_COL_RADIUS	0.31			/* Because 16px * 0.31 ≈ 5px */
# define PLAYER_SPEED		3				/* In cells per second! */
# define PI					3.1415926535	/* Yeah we could use MATH_PI */
# define PLAYER_FOV_DEG		66.0
# define PLAYER_FOV_RAD		(PLAYER_FOV_DEG * PI / 180.0)
# define PLAYER_ROT_SPEED	2.4				/* In radians per second! */

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
	t_uchar		spawn_dir;
	double		collision_radius;
	double		speed;
	double		angle;
}	t_player;

/* player.c */
void		player_init(t_cube *cube);
int			is_player_spawn(u_char c);
void		set_player_spawn(t_cube *cube, int x, int y);
double		player_spawn_angle(t_uchar c);

/* player_movement.c */
void		player_move(t_cube *cube, double dx, double dy);

/* player_input.c */
void		player_handle_input(t_cube *cube);
void		player_update_rotation(t_cube *cube);
t_dcoord	player_dir(t_cube *cube);
t_dcoord	player_right(t_dcoord dir);
void		player_add_move(t_cube *cube, t_dcoord *move,
				t_dcoord dir, t_dcoord right);

/* player_collision.c */
int			player_hits_wall(t_cube *cube, double x, double y);
int			circle_hits_tile(double px, double py, double r, t_coord *tile);
double		clamp_double(double val, double min, double max);

#endif
