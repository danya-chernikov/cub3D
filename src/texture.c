/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:26:39 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/27 12:28:13 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "error.h"

#include "libft.h"

/*  */
int	textures_load(t_cube *cube)
{
	if (!texture_load_one(&cube->tex_files->north, cube->tex_files->north_path))
		return (COMMON_FAILURE);
	if (!texture_load_one(&cube->tex_files->south, cube->tex_files->south_path))
		return (COMMON_FAILURE);
	if (!texture_load_one(&cube->tex_files->west, cube->tex_files->west_path))
		return (COMMON_FAILURE);
	if (!texture_load_one(&cube->tex_files->east, cube->tex_files->east_path))
		return (COMMON_FAILURE);
	return (COMMON_SUCCESS);
}

int	texture_load_one(xpm_t **dst, char *path)
{
	*dst = mlx_load_xpm42(path);
	if (!*dst)
	{
		print_error(MAP_INV_PATH_FILE_ERR);
		return (COMMON_FAILURE);
	}
	return (COMMON_SUCCESS);
}
