/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:27:25 by adeestev          #+#    #+#             */
/*   Updated: 2026/06/05 11:37:37 by adeestev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	assign_tture(const char **tex_path, char *ptr)
{
	int		len;
	char	*path;
	int		fd;

	if (*tex_path != NULL)
		return (print_error("Repeated elements in file"), 0);
	len = 0;
	while (ptr[len] && ptr[len] != ' ' && ptr[len] != '\t'
		&& ptr[len] != '\n' && ptr[len] != '\r')
		len++;
	if (len == 0)
		return (print_error("Texture path or file is invalid"), 0);
	path = ft_substr(ptr, 0, len);
	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (free(path), print_error("Texture path or file is invalid"), 0);
	close(fd);
	*tex_path = path;
	ptr += len;
	ptr = skip_spaces(ptr);
	if (*ptr != '\n' && *ptr != '\0' && *ptr != '\r')
		return (print_error("Identifier is invalid"), 0);
	return (1);
}

static int	parse_texture_or_color(char *ptr, t_cube *c, t_parse_data *d)
{
	if (!ft_strncmp(ptr, "NO", 2) && (ptr[2] == ' ' || ptr[2] == '\t'))
		return (assign_tture(&c->tex_files->north_path, skip_spaces(ptr + 2)));
	if (!ft_strncmp(ptr, "SO", 2) && (ptr[2] == ' ' || ptr[2] == '\t'))
		return (assign_tture(&c->tex_files->south_path, skip_spaces(ptr + 2)));
	if (!ft_strncmp(ptr, "WE", 2) && (ptr[2] == ' ' || ptr[2] == '\t'))
		return (assign_tture(&c->tex_files->west_path, skip_spaces(ptr + 2)));
	if (!ft_strncmp(ptr, "EA", 2) && (ptr[2] == ' ' || ptr[2] == '\t'))
		return (assign_tture(&c->tex_files->east_path, skip_spaces(ptr + 2)));
	if (!ft_strncmp(ptr, "F", 1) && (ptr[1] == ' ' || ptr[1] == '\t'))
	{
		if (d->f_found)
			return (print_error("Repeated elements in file"), 0);
		d->f_found = true;
		return (parse_color(skip_spaces(ptr + 1), &c->floor_color));
	}
	if (!ft_strncmp(ptr, "C", 1) && (ptr[1] == ' ' || ptr[1] == '\t'))
	{
		if (d->c_found)
			return (print_error("Repeated elements in file"), 0);
		d->c_found = true;
		return (parse_color(skip_spaces(ptr + 1), &c->ceiling_color));
	}
	return (print_error("Identifier is invalid"), 0);
}

int	parse_element(char *line, t_cube *cube, t_parse_data *data)
{
	char	*ptr;

	ptr = skip_spaces(line);
	if (!cube->tex_files)
	{
		cube->tex_files = ft_calloc(1, sizeof(t_texture));
		if (!cube->tex_files)
			return (print_error("Memory allocation failed"), 0);
	}
	if (parse_texture_or_color(ptr, cube, data))
		return (data->elements_found++, 1);
	return (0);
}

int	check_all_elements_found(t_parse_data *data, t_cube *cube)
{
	if (data->elements_found < 6)
	{
		if (!cube->tex_files || !cube->tex_files->north_path
			|| !cube->tex_files->south_path || !cube->tex_files->west_path
			|| !cube->tex_files->east_path)
			return (print_error("Texture missing in file"), 0);
		if (!data->f_found || !data->c_found)
			return (print_error("Color missing in file"), 0);
		return (print_error("Missing or invalid configuration elements"), 0);
	}
	return (1);
}

bool	is_element_line(char *line)
{
	char	*p;

	p = skip_spaces(line);
	if (!ft_strncmp(p, "NO", 2) && (p[2] == ' ' || p[2] == '\t'))
		return (true);
	if (!ft_strncmp(p, "SO", 2) && (p[2] == ' ' || p[2] == '\t'))
		return (true);
	if (!ft_strncmp(p, "WE", 2) && (p[2] == ' ' || p[2] == '\t'))
		return (true);
	if (!ft_strncmp(p, "EA", 2) && (p[2] == ' ' || p[2] == '\t'))
		return (true);
	if (!ft_strncmp(p, "F", 1) && (p[1] == ' ' || p[1] == '\t'))
		return (true);
	if (!ft_strncmp(p, "C", 1) && (p[1] == ' ' || p[1] == '\t'))
		return (true);
	return (false);
}
