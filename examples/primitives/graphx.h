/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:11:49 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/05 14:39:34 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHX_H
#define GRAPHX_H

#include "MLX42.h"

#define COMMON_SUCCESS	1
#define COMMON_FAILURE	0

#define BR_DX	0
#define BR_DY	1
#define BR_SX	0
#define BR_SY	1

/* Our graphics data: the image buffer
 * associated with the current window */
typedef struct s_graph_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_graph_data;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

/* Represents a pair of integers.
 * Introduced primarily to comply
 * with the Norm */
typedef struct s_pair_int
{
	int	first;
	int	second;
}	t_pair_int;

/* think - line's thinkness in pixels */
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

/* graphx_common.c */
void	ft_error(void);
void	put_pixel_safe(mlx_image_t *img, int x, int y, uint32_t color);
void	quick_sort_doubles(double *arr, int low, int high);

/* graphx_line.c */
void	draw_line(mlx_image_t *img, t_coord p0, t_coord p1, uint32_t color);
void	bresenham_update_error(t_coord *p0, int *err,
			int deltas[], int steps[]);

/* graphx_line_think.c */
void	draw_line_thick(mlx_image_t *img, t_line *line);
void	draw_girdling_rect(mlx_image_t *img, t_line *line,
	int offset_x, int offset_y);
void	draw_hline(mlx_image_t *img, t_pair_int *x, int y, uint32_t color);
bool	edge_crosses_y(t_coord a, t_coord b, int y);
double	edge_x_at_y(t_coord a, t_coord b, int y);

int		polygon_min_y(t_polygon *poly);
int		polygon_max_y(t_polygon *poly);
int		collect_intersections(t_polygon *poly, int y, double *x_intersections);
void	polygon_fill(mlx_image_t *img, t_polygon *poly);

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
