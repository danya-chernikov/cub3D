/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:53:05 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/20 02:22:13 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "cube.h"

#include <math.h>

/* ============================================================ */
/* Puts a pixel only if it belongs to the minimap area.
 * This clips minimap drawing to its square bounds */
void	minimap_put_pixel(mlx_image_t *img, t_minimap *minimap,
	t_coord *pos, uint32_t color)
{
	if (!in_minimap(minimap, pos->x, pos->y))
		return ;
	put_pixel_safe(img, pos->x, pos->y, color);
}

/* Check if a point with coordinates x and y is
 * inside the minimap's area */
bool	in_minimap(t_minimap *minimap, int x, int y)
{
	if (x < minimap->pos.x || y < minimap->pos.y)
		return (false);
	if (x >= minimap->pos.x + minimap->size)
		return (false);
	if (y >= minimap->pos.y + minimap->size)
		return (false);
	return (true);
}

/* ============================================================ */
/* Converts map cell coordinates to screen coordinates
 * inside our minimap:
 * map cell coordinates -> screen coordinates on minimap.
 * The player is kept in the center of the minimap, so
 * the map appears to scroll around the player
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

/* Same as map_cell_to_minimap(), but works with double coordinates,
 * i.e. with any point in the world, not only with integer map cells.
 * This makes it more generic */
t_coord	world_to_minimap(t_cube *cube, double wx, double wy)
{
	t_coord		screen_coords;
	t_minimap	*minimap;
	double		dx;
	double		dy;

	minimap = &cube->minimap;
	dx = (wx - cube->player.pos.x) * minimap->tile_size;
	dy = (wy - cube->player.pos.y) * minimap->tile_size;
	screen_coords.x = minimap->pos.x + minimap->size / 2 + (int)round(dx);
	screen_coords.y = minimap->pos.y + minimap->size / 2 + (int)round(dy);
	return (screen_coords);
}
