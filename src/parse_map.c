/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 13:11:52 by adeestev          #+#    #+#             */
/*   Updated: 2026/06/10 13:36:46 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
validates that floor or player tile is safe: if the cell touches the boundaries
of the 2D array or a space, it means the wall is unclosed
*/
int	check_neighbors(t_cube *c, t_parse_data *d, int x, int y)
{
	if (x == 0 || y == 0 || x == d->map_width - 1 || y == d->map_height - 1)
		return (0);
	if (c->map[y][x - 1] == ' ' || c->map[y][x + 1] == ' '
		|| c->map[y - 1][x] == ' ' || c->map[y + 1][x] == ' ')
		return (0);
	return (1);
}

/*
safely duplicates a map string and appends it to a temporary linked list (since
total map height is unknown during reading) and tracks the maximum line width
found, which dictates the dimensions for the final 2D array
*/
int	process_map_line(char *line, t_parse_data *data)
{
	t_list	*new_node;
	int		len;
	char	*dup;

	data->map_started = true;
	dup = ft_strdup(line);
	if (!dup)
		return (data->error_flag = true, 0);
	new_node = ft_lstnew(dup);
	if (!new_node)
		return (free(dup), data->error_flag = true, 0);
	ft_lstadd_back(&data->map_lines, new_node);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	if (len > data->map_width)
		data->map_width = len;
	data->map_height++;
	return (1);
}

/*
copies characters from the linked list into a row of the final 2D array and
pads any remaining width with space characters (this force map lines into a
perfect rectangle)
*/
static void	fill_map_row(t_uchar *row, char *line, int width)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		row[i] = (t_uchar)line[i];
		i++;
	}
	while (i < width)
	{
		row[i] = ' ';
		i++;
	}
	row[width] = '\0';
}

/*
allocates the final 2D map array (based on the dimensions calculated during the
reading phase) and prepares the grid for the final validation
*/
int	build_map_array(t_cube *cube, t_parse_data *data)
{
	t_list	*curr;
	int		i;

	if (data->map_height == 0)
		return (0);
	cube->map = ft_calloc(data->map_height + 1, sizeof(t_uchar *));
	if (!cube->map)
		return (0);
	curr = data->map_lines;
	i = 0;
	while (curr)
	{
		cube->map[i] = ft_calloc(data->map_width + 1, sizeof(t_uchar));
		if (!cube->map[i])
			return (0);
		fill_map_row(cube->map[i], (char *)curr->content, data->map_width);
		curr = curr->next;
		i++;
	}
	return (1);
}

/*
prevents grid parsing if the 6 elements haven't been found yet or if end of map
*/
void	handle_map_line(t_cube *cube, t_parse_data *data)
{
	char	*p;

	if (data->elements_found < 6)
	{
		p = skip_spaces(data->line);
		if (*p == '1' || *p == '0' || is_player(*p))
		{
			check_all_elements_found(data, cube);
			data->error_flag = true;
		}
		else if (!parse_element(data->line, cube, data))
			data->error_flag = true;
	}
	else if (data->map_ended)
	{
		print_error(MAP_NOT_LAST_ERR);
		data->error_flag = true;
	}
	else
		process_map_line(data->line, data);
}
