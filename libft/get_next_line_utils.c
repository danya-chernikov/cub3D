/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:48:44 by dchernik          #+#    #+#             */
/*   Updated: 2026/02/25 19:50:58 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

/* Normalize! */
int	gnl_init(char *buf, char **line, long long *v, int *flags)
{
	if (flags[GNL_EXIT])
		return (GNL_BREAK);
	if (flags[GNL_READ])
	{
		if (v[GNL_RLEN] == GNL_BUFFER_SIZE
			&& !flags[GNL_AGAIN] && buf[v[GNL_RLEN] - 1] != '\n')
			flags[GNL_EXIT] = 1;
		flags[GNL_AGAIN] = 0;
		v[GNL_BUF_POS] = 0;
		v[GNL_RLEN] = 0;
		v[GNL_RLEN] = read(v[GNL_FD], buf, GNL_BUFFER_SIZE);
		if (v[GNL_RLEN] <= 0)
		{
			if (v[GNL_RLEN] == -1)
				v[GNL_ERR] = 1;
			if (flags[GNL_EXIT])
			{
				(*line)[v[GNL_LINE_POS] - v[GNL_LINE_LEN] + v[GNL_I]] = '\0';
				return (GNL_RET);
			}
			return (GNL_BREAK);
		}
		flags[GNL_EXIT] = 0;
	}
	return (GNL_NORM);
}

int	gnl_alloc_mem(char **line, long long *v, int *flags)
{
	if (!flags[GNL_ALLOC])
	{
		*line = (char *)malloc((v[GNL_LINE_LEN] + 2) * sizeof (char));
		v[GNL_PRIV_MEM_S] = (v[GNL_LINE_LEN] + 2) * sizeof (char);
	}
	else
	{
		*line = (char *)ft_realloc(*line,
				v[GNL_PRIV_MEM_S], (v[GNL_LINE_POS] + 2) * sizeof (char));
		v[GNL_PRIV_MEM_S] = (v[GNL_LINE_POS] + 2) * sizeof (char);
	}
	if (*line == NULL)
	{
		v[GNL_ERR] = 1;
		return (GNL_BREAK);
	}
	return (GNL_NORM);
}

void	gnl_check_reaching_end(long long *v, int *flags)
{
	if (v[GNL_BUF_POS] == v[GNL_RLEN])
	{
		--v[GNL_BUF_POS];
		flags[GNL_END] = 1;
	}
}

/* Inner interface */
void	gnl_clear_func_state(char **line, long long *v, int *flags)
{
	*line = NULL;
	v[GNL_BUF_POS] = 0;
	v[GNL_LINE_POS] = 0;
	v[GNL_RLEN] = 0;
	v[GNL_I] = 0;
	flags[GNL_EXIT] = 0;
	flags[GNL_READ] = 1;
	flags[GNL_ALLOC] = 0;
	flags[GNL_END] = 0;
	flags[GNL_AGAIN] = 0;
}

/* Outer interface. Used when we need
 * to stop get_next_line() for some
 * reason. However, get_next_line()
 * must always finish reading the entire
 * line from the file descriptor `fd`.
 * Therefore, the caller must use this
 * function if it decides to stop execution,
 * so that gnl_clear_func_state() is called
 * to ensure the correct functioning of all
 * subsequent get_next_line() calls */
void	gnl_finish(int fd)
{
	char	*line;
	int		err;

	err = 0;
	line = get_next_line(fd, &err);
	while (line)
	{
		free(line);
		line = get_next_line(fd, &err);
	}
}
