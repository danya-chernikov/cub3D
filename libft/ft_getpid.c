/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:46:49 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:46:51 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

static int	alg(int fd, pid_t *pid);
static int	check_token(char *line, pid_t *pid);

/* On failure returns -1,
 * on success 0 is returned.
 *     ptokens - process tokens ._. */
int	ft_getpid(pid_t *pid)
{
	int	fd;

	*pid = 0;
	fd = open(PROC_INFO_SOURCE, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (!alg(fd, pid))
		return (-1);
	if (close(fd) == -1)
	{
		perror("close");
		return (-1);
	}
	return (0);
}

/* Returns 1 on success and 0 on failure.
 * It is crucial to allow get_next_line() 
 * to read all lines of the file. Therefore,
 * gnl_clear_func_state() is called at the
 * end of get_next_line() so it can be used
 * safely afterward */
static int	alg(int fd, pid_t *pid)
{
	char	*line;
	int		err;

	err = 0;
	line = get_next_line(fd, &err);
	while (line)
	{
		if (!check_token(line, pid))
			return (0);
		free(line);
		if (*pid != 0)
		{
			gnl_finish(fd);
			return (1);
		}
		line = get_next_line(fd, &err);
	}
	if (!line && err)
	{
		write(STDERR_FILENO, GNL_ERR_MSG, ft_strlen(GNL_ERR_MSG));
		gnl_finish(fd);
		return (0);
	}
	gnl_finish(fd);
	return (1);
}

/* Returns 1 on success and 0 on error */
static int	check_token(char *line, pid_t *pid)
{
	char	**ptokens;
	size_t	tlen;

	ptokens = ft_split(line, ':');
	if (!ptokens)
	{
		write(STDERR_FILENO, SPLIT_ERR_MSG, ft_strlen(SPLIT_ERR_MSG));
		return (0);
	}
	tlen = ft_strlen(PROC_PID_TOKEN);
	if (split_size(ptokens) > 1
		&& !ft_strncmp(ptokens[0], PROC_PID_TOKEN, tlen)
		&& ft_strlen(ptokens[0]) == tlen)
	{
		*pid = ft_atoi(ptokens[1]);
	}
	tlen = ft_strlen(PROC_PPID_TOKEN);
	split_free(&ptokens);
	return (1);
}
