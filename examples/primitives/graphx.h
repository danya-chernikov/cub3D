/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:11:49 by dchernik          #+#    #+#             */
/*   Updated: 2026/05/15 19:31:55 by dchernik         ###   ########.fr       */
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

/* graphx_line.c */
void	draw_line(mlx_image_t *img, t_coord p0, t_coord p1, uint32_t color);
void	draw_line_thick(mlx_image_t *img, t_line *line);


/* graphx_polygon.c */
int		polygon_init(t_polygon *poly, int vert_num);
void	polygon_free(t_polygon *poly);
void	draw_polygon(mlx_image_t *img, t_polygon *poly);


/* graphx_circle.c */


#endif
