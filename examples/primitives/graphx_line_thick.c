#include "graphx.h"

#include <math.h>

/* Draws a line with a specified thickness. We represent our
 * line as a vector (p0; p1). Then we calculate a normal vector
 * (nx; ny) to the (p0; p1). After that, we normalize the normal
 * vector (nx; ny) to unit length and stretch it by multiplying
 * its coordinates by half of the desired line thickness. We
 * call this final transformed vector the 'offset vector', with
 * coordinates (offset_x; offset_y).
 * Next, we draw a rectangle around the initial line represented
 * by p0 and p1. To get one side of this rectangle, we move both
 * endpoints of the line by the (offset) vector. Then, to get the
 * opposite side (parallel to the (p0; p1) vector), we move both
 * endpoints by the negative (offset) vector.
 * In other words, we add/subtract the (offset) vector to/from the
 * coordinates of the line endpoints. Finally, all that remains is
 * to fill this rectangle with the specified color.
 *
 * Link to an explanatory image:
 * https://www.figma.com/design/MOGITOdwaCYQ11DAqgljlT/cub3D?node-id=53-2&
 * t=pOg82eo01UVlwuOu-0
 *
 * nx       - x component of the normal vector (n) to the (p0p1) vector;
 * ny       - y component of the normal vector (n) to the (p0p1) vector;
 * offset_x - x componenet of the normalized normal vector (n), stretched
 *			  by (line->thick / 2);
 * offset_y - y component of the normalized and stretched vector (n);
 * nlen     - length of the normal vector (n). */
void	draw_line_thick(mlx_image_t *img, t_line *line)
{
	double	nx;
	double	ny;
	double	n_len;
	int		offset_x;
	int		offset_y;

	nx = -1 * (line->p1.y - line->p0.y);
	ny = line->p1.x - line->p0.x;
	n_len = sqrt((nx * nx) + (ny * ny));
	if (n_len == 0)
		return ;
	offset_x = round((nx / n_len) * ((double)line->thick / 2.0));
	offset_y = round((ny / n_len) * ((double)line->thick / 2.0));
	draw_girdling_rect(img, line, offset_x, offset_y);
}

/* Just draws a bounding rectable around our line */
void	draw_girdling_rect(mlx_image_t *img, t_line *line,
	int offset_x, int offset_y)
{
	t_coord	a;
	t_coord	b;
	t_coord	c;
	t_coord	d;

	a.x = line->p0.x + offset_x;
	a.y = line->p0.y + offset_y;
	b.x = line->p1.x + offset_x;
	b.y = line->p1.y + offset_y;
	c.x = line->p1.x - offset_x;
	c.y = line->p1.y - offset_y;
	d.x = line->p0.x - offset_x;
	d.y = line->p0.y - offset_y;
	draw_line(img, a, b, line->color);
	draw_line(img, b, c, line->color);
	draw_line(img, c, d, line->color);
	draw_line(img, d, a, line->color);
}

/* Draws a horizontal line (our scanline) at the specified `y` coordinate,
 * from x.first (left endpoint) to x.second (right endpoint) */
void	draw_hline(mlx_image_t *img, t_pair_int *x, int y, uint32_t color)
{
	if (x->first > x->second)
	{
		x->first ^= x->second;
		x->second ^= x->first;
		x->first ^= x->second;
	}
	while (x->first <= x->second)
	{
		put_pixel_safe(img, x->first, y, color);
		++x->first;
	}
}

/* Checks whether the edge represented by the line segment
 * between endpoints `a` and `b` crosses our scanline `y`.
 * Important: this function is applied to each edge separately.
 * Why not do it this way?
 *     min(a.y, b.y) <= y && y <= max(a.y, b.y)
 * Because in that case, each vertex of the polygon would
 * be counted twice, since each vertex also belongs to the
 * next edge of the polygon */
bool	edge_crosses_y(t_coord a, t_coord b, int y)
{
	if (a.y <= y && b.y > y)
		return (true);
	if (b.y <= y && a.y > y)
		return (true);
	return (false);
}

/* Determines the x coordinate of the intersection point
 * between our scanline and an edge by performing so-called
 * linear interpolation.
 * Link to an explanatory image:
 * https://www.figma.com/design/MOGITOdwaCYQ11DAqgljlT/cub3D?node-id=79-2&
 * t=tPmVaatPcz9EXQV9-0 */
double	edge_x_at_y(t_coord a, t_coord b, int y)
{
	return (a.x + (double)(y - a.y) * (b.x - a.x) / (b.y - a.y));
}
