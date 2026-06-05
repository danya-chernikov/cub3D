/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 13:12:49 by adeestev          #+#    #+#             */
/*   Updated: 2026/06/05 11:31:31 by adeestev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

static int	check_islands(t_cube *c, t_parse_data *d)
{
	int	y;
	int	x;

	d->vis = ft_calloc(d->map_height, sizeof(char *));
	if (!d->vis)
		return (print_error("Memory allocation failed"), 0);
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
					print_error("Disconnected map found"), 0);
	}
	return (free_vis(d->vis, d->map_height), 1);
}

static int	check_cell(t_cube *c, t_parse_data *d, int x, int y)
{
	char	cell;

	cell = c->map[y][x];
	if (cell != '0' && cell != '1' && cell != ' ' && !is_player(cell))
	{
		if ((cell >= 'a' && cell <= 'z') || (cell >= 'A' && cell <= 'Z'))
			return (print_error("Player's direction is invalid"), 0);
		return (print_error("Map contains an invalid character"), 0);
	}
	if (is_player(cell))
	{
		d->player_count++;
		d->px = x;
		d->py = y;
	}
	if ((cell == '0' || is_player(cell)) && !check_neighbors(c, d, x, y))
		return (print_error("Map is not surrounded by walls"), 0);
	return (1);
}

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
		return (print_error("Map must contain exactly one player"), 0);
	return (check_islands(c, d));
}
