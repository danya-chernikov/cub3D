/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:53:05 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/08 20:59:30 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "cube.h"

#include <math.h>

/* ============================================================ */
/* Puts a pixel only if it belongs to the minimap area.
 * This clips minimap drawing to its square bounds */
void	minimap_put_pixel(mlx_image_t *img, t_minimap *minimap,
	int x, int y, uint32_t color)
{
	if (!in_minimap(minimap, x, y))
		return ;
	put_pixel_safe(img, x, y, color);
}

/* Check if a point with coordinates x and y is
 * inside the minimap's area. If a point is inside
 * the map returns true */
int	in_minimap(t_minimap *minimap, int x, int y)
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
/* Checks whether the map cell at coordinates (x, y)
 * should be treated as a wall. Cells outside the map
 * and spaces are also treated as walls */
int	map_cell_is_wall(t_cube *cube, int x, int y)
{
	if (y < 0 || y >= cube->map_height)
		return (true);
	if (x < 0 || x >= map_row_len(cube->map[y]))
		return (true);
	if (cube->map[y][x] == '1')
		return (true);
	if (cube->map[y][x] == ' ')
		return (true);
	return (false);
}

/* Returns the length of a map row.
 * (Our map easily may be non-rectangular) */
int	map_row_len(u_char *row)
{
	int	len;

	len = 0;
	while (row && row[len])
		++len;
	return (len);
}

/* ============================================================ */
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
