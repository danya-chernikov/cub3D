#ifndef MINIMAP_H
# define MINIMAP_H

/* Coordinates as extended
 * presision floating point */
typedef struct s_dcoord
{
	double	x;
	double	y;
}	t_dcoord;

/* Player's coordinates on
 * the 2D minimap.
 *     pos    - player's coordinates in map cells;
 *     radius - player's physical radius on the minimap,
 *				measured in map cells. */
typedef struct s_player
{
	t_dcoord	pos;	
	double		collision_radius;
	double		speed;
}	t_player;

/* Represents our 2D minimap.
 *     pos			 - minimap's position in the main window;
 *     size			 - minimap's size in pixels;
 *     tile_size	 - how many pixels one map cell occupies on the minimap;
 *     player_radius - player's visual radius on the minimap, in pixels. */
typedef struct s_minimap
{
	t_coord		pos;
	int			size;
	int			tile_size;
	int			player_radius_px;
	uint32_t	bg_color;
	uint32_t	wall_color;
	uint32_t	bg_color;
}	t_minimap;

/* Helper structure that represents a rectangle
 * for drawing a minimap */
typedef struct s_rect
{
	t_coord		pos;
	int			w;
	int			h;
	uint32_t	color;
}	t_rect;

#endif
