/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getgid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:45:13 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:45:14 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int	parse_first_gid_from_status(gid_t *out);
static void	extract_gid(gid_t *out, char *line);
static void	free_all(int *fd, char *line);

int	ft_getgid(gid_t *gid)
{
	if (!gid)
		return (-1);
	return (parse_first_gid_from_status(gid));
}

static int	parse_first_gid_from_status(gid_t *out)
{
	int		fd;
	int		err;
	char	*line;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
		return (perror("open"), -1);
	err = 0;
	line = get_next_line(fd, &err);
	while (line)
	{
		if (!ft_strncmp(line, "Gid:", 4))
		{
			extract_gid(out, line);
			free_all(&fd, line);
			return (0);
		}
		free(line);
		line = get_next_line(fd, &err);
	}
	if (err)
		perror("get_next_line");
	gnl_finish(fd);
	close(fd);
	return (-1);
}

static void	extract_gid(gid_t *out, char *line)
{
	char	*p;

	p = line + 4;
	while (*p == ' ' || *p == '\t')
		++p;
	*out = (gid_t)ft_atoi(p);
}

static void	free_all(int *fd, char *line)
{
	free(line);
	gnl_finish(*fd);
	close(*fd);
}
