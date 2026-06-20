/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:06:45 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/19 13:55:10 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "cube.h"

/* For now let's draw a square minimap */
void	minimap_init(t_cube *cube, t_coord pos)
{
	cube->minimap.pos = pos;
	cube->minimap.size = MINIMAP_SIZE;
	cube->minimap.tile_size = MINIMAP_TILE_SIZE;
	cube->minimap.player_radius_px = PLAYER_RADIUS;
	cube->minimap.bg_color = COLOR_ALMOST_BLACK;
	cube->minimap.wall_color = COLOR_GRAY;
	cube->minimap.player_color = COLOR_BLUE;
}

void	minimap_draw(mlx_image_t *img, t_cube *cube)
{
	minimap_draw_background(img, &cube->minimap);
	minimap_draw_walls(img, cube);
	minimap_draw_fov(img, cube);
	minimap_draw_player(img, cube);
}

void	minimap_draw_player(mlx_image_t *img, t_cube *cube)
{
	t_coord	center;	

	center.x = cube->minimap.pos.x + cube->minimap.size / 2;
	center.y = cube->minimap.pos.y + cube->minimap.size / 2;
	circle_filled_draw(img, center, cube->minimap.player_radius_px,
		cube->minimap.player_color);
}

/* Draws the minimap backgound as a filled square */
void	minimap_draw_background(mlx_image_t *img, t_minimap *minimap)
{
	t_rect	bg;

	bg.pos = minimap->pos;
	bg.w = minimap->size;
	bg.h = minimap->size;
	bg.color = minimap->bg_color;
	minimap_fill_rect(img, minimap, bg);
}

/* Fills a rectangle with the specified color,
 * clipping every pixel to the minimap area */
void	minimap_fill_rect(mlx_image_t *img, t_minimap *minimap, t_rect r)
{
	t_coord	p;

	p.y = r.pos.y;
	while (p.y < r.pos.y + r.h)
	{
		p.x = r.pos.x;
		while (p.x < r.pos.x + r.w)
		{
			minimap_put_pixel(img, minimap, &p, r.color);
			++p.x;
		}
		++p.y;
	}
}
