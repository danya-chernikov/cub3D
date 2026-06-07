/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:51:23 by adeestev          #+#    #+#             */
/*   Updated: 2026/06/05 11:28:53 by adeestev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cube.h"
# include "libft.h"
# include "error.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_parse_data
{
	int		fd;
	char	*line;
	int		elements_found;
	bool	map_started;
	bool	map_ended;
	t_list	*map_lines;
	int		player_count;
	int		map_width;
	int		map_height;
	bool	error_flag;
	bool	f_found;
	bool	c_found;
	bool	has_content;
	int		px;
	int		py;
	char	**vis;
}	t_parse_data;

// parser.c
int		parse_cub_file(const char *filename, t_cube *cube);

// parse_elements.c
int		parse_element(char *line, t_cube *cube, t_parse_data *data);
int		check_all_elements_found(t_parse_data *data, t_cube *cube);
bool	is_element_line(char *line);

// parse_color.c
int		parse_color(char *line, uint32_t *color);

// parse_map.c
int		process_map_line(char *line, t_parse_data *data);
int		build_map_array(t_cube *cube, t_parse_data *data);
int		check_neighbors(t_cube *c, t_parse_data *d, int x, int y);
void	handle_map_line(t_cube *cube, t_parse_data *data);

// parse_validation.c
int		validate_map(t_cube *cube, t_parse_data *data);

// parser_utils.c
void	free_parse_data(t_parse_data *data);
void	free_cube(t_cube *cube);
char	*skip_spaces(char *str);
int		is_player(char c);

#endif
