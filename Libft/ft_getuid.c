/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getuid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:46:22 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:46:23 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int	parse_first_id_from_status(const char *key, uid_t *out);
static void	extract_uid(uid_t *out, char *line, const char *key);

int	ft_getuid(uid_t *uid)
{
	if (!uid)
		return (-1);
	return (parse_first_id_from_status("Uid:", uid));
}

static int	parse_first_id_from_status(const char *key, uid_t *out)
{
	int		fd;
	char	*line;
	int		err;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
		return (perror("open"), -1);
	err = 0;
	line = get_next_line(fd, &err);
	while (line)
	{
		if (!ft_strncmp(line, key, ft_strlen(key)))
		{
			extract_uid(out, line, key);
			return (free(line), gnl_finish(fd), close(fd), 0);
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

static void	extract_uid(uid_t *out, char *line, const char *key)
{
	char	*p;

	p = line + ft_strlen(key);
	while (*p == ' ' || *p == '\t')
		++p;
	*out = (uid_t)ft_atoi(p);
}
