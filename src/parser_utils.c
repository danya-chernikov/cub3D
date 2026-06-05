/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:06:32 by adeestev          #+#    #+#             */
/*   Updated: 2026/06/05 11:33:12 by adeestev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*skip_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	free_parse_data(t_parse_data *data)
{
	if (data->fd >= 0)
	{
		gnl_finish(data->fd);
		close(data->fd);
	}
	if (data->line)
		free(data->line);
	if (data->map_lines)
		ft_lstclear(&data->map_lines, free);
}

static void	free_texture(t_texture *tex)
{
	if (!tex)
		return ;
	if (tex->north_path)
		free((void *)tex->north_path);
	if (tex->south_path)
		free((void *)tex->south_path);
	if (tex->west_path)
		free((void *)tex->west_path);
	if (tex->east_path)
		free((void *)tex->east_path);
	free(tex);
}

void	free_cube(t_cube *cube)
{
	int	i;

	if (!cube)
		return ;
	free_texture(cube->tex_files);
	if (cube->map)
	{
		i = 0;
		while (cube->map[i])
		{
			free(cube->map[i]);
			i++;
		}
		free(cube->map);
	}
	free(cube);
}
