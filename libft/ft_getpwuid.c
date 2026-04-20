/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpwuid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 20:47:05 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/27 00:30:22 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <linux/limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int	passwd_attempt(t_passwd *pwd, int fd, uid_t uid);
static void	passwd_attempt_clearner(char ***ptokens, char *line, int fd);
static int	check_and_split(char ***ptokens, char *line, int *fd);
static void	free_line_and_split(char ***ptokens, char *line);
static void	passwd_attempt_clearner(char ***ptokens, char *line, int fd);

/* Attempts to fill the pwd structure with
 * the parsed fields of the record in
 * `/etc/passwd` that matches the `uid`
 * passed as the second argument. If
 * `/etc/passwd` does not contain a record
 * with this UID, it attempts to open each
 * directory in /home and determine the owner
 * UID of each directory using stat(). It then
 * compares each UID with the given `uid` to
 * find the corresponding username. If this
 * function returns -1, it means only one thing:
 * malloc() failed or a system error occurred.
 * If returns 0 it means it could not retreive
 * the user's data. And 1 is returned on success */
int	ft_getpwuid(t_passwd *pwd, uid_t uid)
{
	int	fd;
	int	res;

	ft_memset(pwd, 0, sizeof(*pwd));
	fd = open(PASSWD_PATH, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	res = passwd_attempt(pwd, fd, uid);
	if (res == 0)
		res = home_attempt(pwd, uid);
	if (close(fd) == -1)
	{
		perror("close");
		return (-1);
	}
	return (res);
}

/* On success returns 1, when failed to match UID it will return 0,
 * and on malloc() error -1.
 *     ptokens - passwd tokens ._. */
static int	passwd_attempt(t_passwd *pwd, int fd, uid_t uid)
{
	char	*line;
	char	**ptokens;
	int		err;

	err = 0;
	line = get_next_line(fd, &err);
	while (line)
	{
		if (check_and_split(&ptokens, line, &fd) == -1)
			return (-1);
		if (split_size(ptokens) > 2 && ft_atoi(ptokens[2]) == (int)uid)
		{
			if (!fill_pwd_struct(pwd, ptokens, uid))
				return (passwd_attempt_clearner(&ptokens, line, fd), -1);
			return (passwd_attempt_clearner(&ptokens, line, fd), 1);
		}
		free_line_and_split(&ptokens, line);
		line = get_next_line(fd, &err);
	}
	if (!line && err)
	{
		write(STDERR_FILENO, GNL_ERR_MSG, ft_strlen(GNL_ERR_MSG));
		return (gnl_finish(fd), -1);
	}
	return (gnl_finish(fd), 0);
}

static int	check_and_split(char ***ptokens, char *line, int *fd)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	*ptokens = ft_split(line, ':');
	if (!(*ptokens))
		return (free(line), perror("malloc"), gnl_finish(*fd), -1);
	return (1);
}

static void	free_line_and_split(char ***ptokens, char *line)
{
	free(line);
	split_free(ptokens);
}

static void	passwd_attempt_clearner(char ***ptokens, char *line, int fd)
{
	free(line);
	gnl_finish(fd);
	split_free(ptokens);
}
