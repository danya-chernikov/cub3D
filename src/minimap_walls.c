/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 19:00:45 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/14 16:08:03 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "cube.h"

/* Draws all visible draw tiles around the player. Only the
 * cells that can appear inside the minimap area are checked
 * and rendered.
 *     half_cells - number of cells checked from the player's
 *					current cell to each edge of the map
 *					(radius of the visible minimap area).
 *					We add 2 as a buffer
 * More info:
 * https://www.figma.com/design/MOGITOdwaCYQ11DAqgljlT/cub3D?
 * node-id=178-4&t=5nIXqabU7V6JhGvL-0*/
void	minimap_draw_walls(mlx_image_t *img, t_cube *cube)
{
	int	half_cells;
	int	x;
	int	y;

	half_cells = ((cube->minimap.size / 2) / cube->minimap.tile_size) + 2;
	y = (int)cube->player.pos.y - half_cells;
	while (y <= (int)cube->player.pos.y + half_cells)
	{
		x = (int)cube->player.pos.x - half_cells;
		while (x <= (int)cube->player.pos.x + half_cells)
		{
			if (map_cell_is_visible_wall(cube, x, y))
				minimap_draw_wall(img, cube, x, y);
			++x;
		}
		++y;
	}
}

/* Draws one wall tile on the minimap. The tile is converted from
 * map coordinates to minimap screen coordinates before drawing */
void	minimap_draw_wall(mlx_image_t *img, t_cube *cube, int mx, int my)
{
	t_rect	r;

	r.pos = map_cell_to_minimap(cube, mx, my);
	r.w = cube->minimap.tile_size;
	r.h = cube->minimap.tile_size;
	r.color = cube->minimap.wall_color;
	minimap_fill_rect(img, &cube->minimap, r);
}

/* For collision detection.
 * Checks whether the map cell at coordinates (x, y)
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

/* For minimap walls drawing */
int	map_cell_is_visible_wall(t_cube *cube, int x, int y)
{
	if (y < 0 || y >= cube->map_height)
		return (false);
	if (x < 0 || x >= map_row_len(cube->map[y]))
		return (false);
	if (cube->map[y][x] == '1')
		return (true);
	return (false);
}

/* Returns the length of a map row.
 * (Our map easily may be non-rectangular) */
int	map_row_len(t_uchar *row)
{
	int	len;

	len = 0;
	while (row && row[len])
		++len;
	return (len);
}
