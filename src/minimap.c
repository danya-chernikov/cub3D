#include "minimap.h"

#include <stdbool.h>

/* Check if a point with coordinates x and y is inside
 * the minimap's area */
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

/* Puts a pixel only if it belongs to the minimap area.
 * This clips minimap drawing to its square bounds */
void	minimap_put_pixel(mlx_image_t *img, t_minimap *minimap,
	int x, int y, uint32_t color)
{
	if (!in_minimap(minimap, x, y))
		return ;
	put_pixel_safe(img, x, y, color);
}

/* Fills a rectangle with the specified color,
 * clipping every pixel to the minimap area */
void	minimap_fill_rect(mlx_image_t *img, t_minimap *minimap, t_rect r)
{
	int	x;
	int	y;

	y = r.pos.y;
	while (y < r.pos.x + r.h)
	{
		x = r.pos.x;
		while (x < r.pos.x + r.w)
		{
			minimap_put_pixel(img, minimap, x, y, r.color);
			++x;
		}
		++y;
	}
}

/* Returns the length of a map row.
 * (Our map easily may be non-rectangular) */
int	map_row_len(u_char *row)
{
	int	i;

	i = 0;
	while (row && row[i])
		++i;
	return (i);
}
