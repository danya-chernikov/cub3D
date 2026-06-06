#ifndef MINIMAP_H
# define MINIMAP_H

/* Coordinates as extended
 * presision floating point */
typedef struct s_dcoord
{
	double	x;
	double	y;
}	t_dcoord;

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

/* Represents our 2D minimap.
 *     pos				- minimap's position in the main window;
 *     size				- minimap's size in pixels;
 *     tile_size	    - how many pixels one map cell occupies on the minimap;
 *     player_radius_px - player's visual radius on the minimap, in pixels. */
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

/* minimap.c */
int		in_minimap(t_minimap *minimap, int x, int y);
void	minimap_put_pixel(mlx_image_t *img, t_minimap *minimap,
	int x, int y, uint32_t color);
void	minimap_fill_rect(mlx_image_t *img, t_minimap *minimap, t_rect r);
int		map_row_len(u_char *row);
int		map_cell_is_wall(t_cube *cube, int x, int y);

/* minimap2.c */
t_coord	map_cell_to_minimap(t_cube *cube, int mx, int my);





#endif
