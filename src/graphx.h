/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:11:49 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/29 04:09:26 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHX_H
# define GRAPHX_H

# include "MLX42.h"

/* For Bresenham's algorithm */
# define BR_DX				0
# define BR_DY				1
# define BR_SX				0
# define BR_SY				1

/* Window parameters */
# define WIN_WIDTH			1920
# define WIN_HEIGHT			1080

/* Basic colors */
# define COLOR_WHITE		0x00000000FF
# define COLOR_BACK			0x00FFFFFFFF
# define COLOR_RED			0x00FF0000FF
# define COLOR_BLUE			0x000000FFFF
# define COLOR_GREEN		0x0000FF00FF
# define COLOR_YELLOW		0x00FFFF00FF
# define COLOR_CYAN			0x0000FFFFFF
# define COLOR_PURPLE		0x00FF00FFFF
# define COLOR_GRAY			0x00777777FF
# define COLOR_LIGHT_GRAY	0x00B7B4B7FF
# define COLOR_BROWN		0x00895129FF
# define COLOR_ORANGE		0x00FF6A00FF
# define COLOR_PINK			0x00FF008CFF
# define COLOR_ALMOST_BLACK	0x00202020FF
# define COLOR_ALMOST_WHITE	0x00EDEDEDFF
# define COLOR_BLUISH		0x00B8DEF7FF

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

/* Coordinates as extended
 * presision floating point */
typedef struct s_dcoord
{
	double	x;
	double	y;
}	t_dcoord;

/* Represents a pair of integers.
 * Introduced primarily to comply
 * with the Norm */
typedef struct s_pair_int
{
	int	first;
	int	second;
}	t_pair_int;

/* Our graphics data: the image buffer
 * associated with the current window */
typedef struct s_graph_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int32_t		win_width;
	int32_t		win_height;
}	t_graph_data;

/* thick - line's thinkness in pixels */
typedef struct s_line
{
	t_coord		p0;
	t_coord		p1;
	uint32_t	color;
	int			thick;
}	t_line;

typedef struct s_polygon
{
	t_coord		*vertices;
	int			vert_num;
	int			thick;
	uint32_t	color;
}	t_polygon;

/* graphx_utils.c */
void	graphx_error(void);
void	put_pixel_safe(mlx_image_t *img, int x, int y, uint32_t color);
void	quick_sort_doubles(double *arr, int low, int high);

/* graphx_window.c */
void	graphx_resize_hook(int32_t width, int32_t height, void *param);

/* graphx_line.c */
void	draw_line(mlx_image_t *img, t_coord p0, t_coord p1, uint32_t color);
void	bresenham_update_error(t_coord *p0, int *err,
			int deltas[], int steps[]);

/* graphx_line_thick.c */
void	draw_line_thick(mlx_image_t *img, t_line *line);
void	draw_girdling_rect(mlx_image_t *img, t_line *line,
			int offset_x, int offset_y);
void	draw_hline(mlx_image_t *img, t_pair_int *x, int y, uint32_t color);
bool	edge_crosses_y(t_coord a, t_coord b, int y);
double	edge_x_at_y(t_coord a, t_coord b, int y);

/* graphx_polygon.c */
int		polygon_init(t_polygon *poly, int vert_num);
void	polygon_free(t_polygon *poly);
void	polygon_draw(mlx_image_t *img, t_polygon *poly);
int		polygon_min_y(t_polygon *poly);
int		polygon_max_y(t_polygon *poly);

/* graphx_polygon2.c */
int		collect_intersections(t_polygon *poly, int y, double *x_intersections);
void	polygon_fill(mlx_image_t *img, t_polygon *poly);

/* graphx_circle.c */
void	circle_draw(mlx_image_t *img, t_coord center,
			int radius, uint32_t color);
void	circle_filled_draw(mlx_image_t *img, t_coord center,
			int radius, uint32_t color);

#endif
