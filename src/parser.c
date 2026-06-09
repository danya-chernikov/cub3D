/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:52:43 by adeestev          #+#    #+#             */
/*   Updated: 2026/06/09 18:23:30 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
validates that file has the correct extension
*/
static int	check_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

/*
initializes temporary parsing workspace to safe values:
(to prevent undefined behavior and ensure that cleanup functions do not
free uninitialized memory if parsing fails early)
*/
static void	init_parse_data(t_parse_data *data)
{
	/* I guess here we could use just:
	 * ft_bzero(data, sizeof(*data)); */
	data->fd = -1;
	data->line = NULL;
	data->elements_found = 0;
	data->map_started = false;
	data->map_ended = false;
	data->map_lines = NULL;
	data->player_count = 0;
	data->map_width = 0;
	data->map_height = 0;
	data->error_flag = false;
	data->f_found = false;
	data->c_found = false;
	data->has_content = false;
	data->vis = NULL;
}

/*
the central router for the parsing loop: (it evaluates a single line)
- empty lines before the map are ignored
- empty lines after map has started triggers map_ended flag
(ensuring map is last element in file) 
- configuration elements are sent to parse_element
- if element appears after the map starts means error
- if not empty and not element, it is sent to handle_map_line
*/
static void	handle_line(t_cube *cube, t_parse_data *data)
{
	bool	is_empty;

	data->has_content = true;
	is_empty = (*skip_spaces(data->line) == '\n'
			|| *skip_spaces(data->line) == '\0');
	if (is_empty && data->map_started)
		data->map_ended = true;
	else if (is_empty)
		return ;
	else if (is_element_line(data->line))
	{
		if (data->map_started || data->map_ended)
		{
			print_error("Map is not last element in file");
			data->error_flag = true;
		}
		else if (!parse_element(data->line, cube, data))
			data->error_flag = true;
	}
	else
		handle_map_line(cube, data);
}

/*
iterates through the file line by line:
for every line, it calls handle_line and then immediately frees the line
pointer and sets it to NULL (guarantees that no double-frees or dangling
pointers occur during the reading process)
*/
static int	read_file_lines(t_cube *cube, t_parse_data *data)
{
	int	err;

	err = 0;
	data->line = get_next_line(data->fd, &err);
	while (data->line != NULL && !data->error_flag)
	{
		handle_line(cube, data);
		free(data->line);
		data->line = NULL;
		if (!data->error_flag)
			data->line = get_next_line(data->fd, &err);
	}
	if (err || data->error_flag)
		return (0);
	return (1);
}

/*
the main parsing part:
- creates temporary workspace and initialize it
- verify extension and open file safely
- extract elements and map lines into the linked list.
- ensure 6 elements and map content are present
- convert the linked list into a 2D array
- run validations (walls, characters, flood-fill)
- cleans up the workspace and return the t_cube
*/
int	parse_cub_file(const char *filename, t_cube *cube)
{
	t_parse_data	data;

	init_parse_data(&data);
	if (!check_extension(filename))
		return (print_error("Invalid file extension. Expected .cub"), 0);
	data.fd = open(filename, O_RDONLY);
	if (data.fd < 0)
		return (print_error("Cannot open file"), 0);
	if (!read_file_lines(cube, &data))
		return (free_parse_data(&data), 0);
	if (!data.has_content)
		return (print_error("No content in file"), free_parse_data(&data), 0);
	if (!check_all_elements_found(&data, cube))
		return (free_parse_data(&data), 0);
	if (data.map_height == 0)
		return (print_error("Missing map in file"), free_parse_data(&data), 0);
	if (!build_map_array(cube, &data) || !validate_map(cube, &data))
		return (free_parse_data(&data), 0);
	cube->map_width = data.map_width;
	cube->map_height = data.map_height;
	free_parse_data(&data);
	return (1);
}
