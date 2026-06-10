/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 13:12:49 by adeestev          #+#    #+#             */
/*   Updated: 2026/06/10 11:41:25 by adeestev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
flood-fill algorithm:
it stops when hitting map boundaries, spaces or previously visited cells
*/
static void	flood_fill_cont(t_cube *c, t_parse_data *d, int x, int y)
{
	if (x < 0 || y < 0 || x >= d->map_width || y >= d->map_height)
		return ;
	if (c->map[y][x] == ' ' || d->vis[y][x])
		return ;
	d->vis[y][x] = 1;
	flood_fill_cont(c, d, x + 1, y);
	flood_fill_cont(c, d, x - 1, y);
	flood_fill_cont(c, d, x, y + 1);
	flood_fill_cont(c, d, x, y - 1);
}

/*
frees the temporary boolean array used by the flood-fill algorithm
*/
static void	free_vis(char **vis, int height)
{
	int	i;

	i = 0;
	if (!vis)
		return ;
	while (i < height)
	{
		if (vis[i])
			free(vis[i]);
		i++;
	}
	free(vis);
}

/*
allocates the "vis" array, triggers the flood-fill and scans the entire map;
if it finds a valid wall or floor tile that the algorithm couldn't reach, it
rejects the file for containing a disconnected map island
*/
static int	check_islands(t_cube *c, t_parse_data *d)
{
	int	y;
	int	x;

	d->vis = ft_calloc(d->map_height, sizeof(char *));
	if (!d->vis)
		return (print_error(MAP_MALLOC_ERR), 0);
	y = -1;
	while (++y < d->map_height)
	{
		d->vis[y] = ft_calloc(d->map_width, sizeof(char));
		if (!d->vis[y])
			return (free_vis(d->vis, d->map_height), 0);
	}
	flood_fill_cont(c, d, d->px, d->py);
	y = -1;
	while (++y < d->map_height)
	{
		x = -1;
		while (++x < d->map_width)
			if (c->map[y][x] != ' ' && !d->vis[y][x])
				return (free_vis(d->vis, d->map_height),
					print_error(MAP_ISLAND_ERR), 0);
	}
	return (free_vis(d->vis, d->map_height), 1);
}

/*
validates map cell with allowed chars and ensure the map is perfectly surrounded
by walls.
*/
static int	check_cell(t_cube *c, t_parse_data *d, int x, int y)
{
	char	cell;

	cell = c->map[y][x];
	if (cell != '0' && cell != '1' && cell != ' ' && !is_player(cell))
	{
		if ((cell >= 'a' && cell <= 'z') || (cell >= 'A' && cell <= 'Z'))
			return (print_error(MAP_PLAYER_DIR_ERR), 0);
		return (print_error(MAP_INV_CHAR_ERR), 0);
	}
	if (is_player(cell))
	{
		d->player_count++;
		d->px = x;
		d->py = y;
	}
	if ((cell == '0' || is_player(cell)) && !check_neighbors(c, d, x, y))
		return (print_error(MAP_OUTLINE_ERR), 0);
	return (1);
}

/*
final map inspection loop:
it iterates over every single cell calling check_cell on each,
verifies that only one player was found and triggers the flood-fill check
*/
int	validate_map(t_cube *c, t_parse_data *d)
{
	int	x;
	int	y;

	y = -1;
	while (++y < d->map_height)
	{
		x = -1;
		while (++x < d->map_width)
			if (!check_cell(c, d, x, y))
				return (0);
	}
	if (d->player_count != 1)
		return (print_error(MAP_ONE_PLAYER_ERR), 0);
	return (check_islands(c, d));
}
