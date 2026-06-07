#include "minimap.h"

/* Converts map cell coordinates to screen coordinates
 * inside our minimap:
 * map cell coordinates -> screen coordinates on minimap.
 * The player is kept in the center of the minimap, so
 * the map appears to scroll around the player (at least
 * I wanna acheive this..)
 *     mx - x coordinate on the minimap;
 *     my - y coordinate on the minimap. */
t_coord	map_cell_to_minimap(t_cube *cube, int mx, int my)
{
	t_coord		screen_coords;
	t_minimap	*minimap;
	double		dx;
	double		dy;

	minimap = &cube->minimap;
	dx = (mx - cube->player.pos.x) * minimap->tile_size;
	dy = (my - cube->player.pos.y) * minimap->tile_size;
	screen_coords.x = minimap->pos.x + minimap->size / 2 + (int)round(dx);
	screen_coords.y = minimap->pos.y + minimap->size / 2 + (int)round(dy);
	return (screen_coords);
}

/* Draws one wall tile on the minimap. The tile is converted from
 * map coordinates to minimap screen coordinates before drawing */
void	minimap_draw_wall(mlx_image_t *img, t_cube *cube, int mx, int my)
{
	t_rect	r;

	r.pos = map_to_minimap(cube, mx, my);
	r.w = cube->minimap.tile_size;
	r.h = cube->minimap.tile_size;
	r.color = cube->minimap.wall_color;
	minimap_fill_rect(img, &cube->minimap, r);
}

/* Draws the minimap backgound as a filled square */
void	minimap_draw_bg(mlx_image_t *img, t_minimap *minimap)
{
	t_rect	bg;

	bg.pos = minimap->pos;
	bg.w = minimap->size;
	bg.h = minimap->size;
	bg.color = minimap->color;
	minimap_fill_rect(img, minimap, bg);
}

/*void	minimap_draw_walls(mlx_image_t *img, t_cube *cube)
{
}*/

void	minimap_draw_player(mlx_image_t *img, t_cube *cube)
{
	t_coord	center;	

	center.x = cube->minimap.pos.x + cube->minimap.size / 2;
	center.y = cube->minimap.pos.y + cube->minimap.size / 2;
	circle_filled_draw(img, center, cube->minimap.player_radius_px,
		cube->minimap.player_color);
}

void	minimap_draw(mlx_image_t *img, t_cube *cube)
{
	minimap_draw_background();
	//minimap_draw_walls(img, cube);
	minimap_draw_player(img, cube);
}
