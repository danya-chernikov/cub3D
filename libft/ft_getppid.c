/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getppid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:46:14 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 20:46:15 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

static int	alg(int fd, pid_t *ppid);
static int	check_token(char *line, pid_t *ppid);

/* On failure `errcode` will be -1,
 * on success 0 is returned.
 *     ptokens - process tokens ._. */
int	ft_getppid(pid_t *ppid)
{
	int	fd;

	*ppid = 0;
	fd = open(PROC_INFO_SOURCE, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (!alg(fd, ppid))
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
static int	alg(int fd, pid_t *ppid)
{
	char	*line;
	int		err;

	err = 0;
	line = get_next_line(fd, &err);
	while (line)
	{
		if (!check_token(line, ppid))
			return (0);
		free(line);
		if (*ppid != 0)
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
static int	check_token(char *line, pid_t *ppid)
{
	char	**ptokens;
	size_t	tlen;

	ptokens = ft_split(line, ':');
	if (!ptokens)
	{
		write(STDERR_FILENO, SPLIT_ERR_MSG, ft_strlen(SPLIT_ERR_MSG));
		return (0);
	}
	tlen = ft_strlen(PROC_PPID_TOKEN);
	if (split_size(ptokens) > 1
		&& !ft_strncmp(ptokens[0], PROC_PPID_TOKEN, tlen)
		&& ft_strlen(ptokens[0]) == tlen)
	{
		*ppid = ft_atoi(ptokens[1]);
	}
	tlen = ft_strlen(PROC_PPID_TOKEN);
	split_free(&ptokens);
	return (1);
}
