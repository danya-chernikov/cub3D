/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 19:00:45 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/08 20:50:05 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "cube.h"

/*void	minimap_draw_walls(mlx_image_t *img, t_cube *cube)
{

}*/

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
