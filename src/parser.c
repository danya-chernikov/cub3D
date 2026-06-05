/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:52:43 by adeestev          #+#    #+#             */
/*   Updated: 2026/06/05 17:32:18 by adeestev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static void	init_parse_data(t_parse_data *data)
{
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

static void	handle_line(t_cube *cube, t_parse_data *data)
{
	bool	is_emp;

	data->has_content = true;
	is_emp = (*skip_spaces(data->line) == '\n'
			|| *skip_spaces(data->line) == '\0');
	if (is_emp && data->map_started)
		data->map_ended = true;
	else if (is_emp)
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
	free_parse_data(&data);
	return (1);
}
