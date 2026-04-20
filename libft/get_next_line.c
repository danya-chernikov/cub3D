/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:48:41 by dchernik          #+#    #+#             */
/*   Updated: 2026/01/23 16:31:02 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The `v` array was defined as long long
 * to be able to fit into it both variables
 * of size_t and int types.
 *     v - the array holding variables.
 * We call gnl_clear_func_state() in case of
 * an error and if it was completed successfully
 * by finished reading all the lines from the file `fd`.
 * HOWEVER, if caller decides to stop the execution of
 * get_next_line() he MUST call gnl_finish() which
 * continues reading all rest lines from `fd` until
 * the last one, so gnl_clear_func_state() could be
 * called */
char	*get_next_line(int fd, int *err)
{
	static char			buf[GNL_BUFFER_SIZE];
	static char			*line = NULL;
	static int			flags[5] = {0, 1, 0, 0, 0};
	static long long	v[9];

	v[GNL_ERR] = *err;
	v[GNL_FD] = (long long)fd;
	if (v[GNL_BUF_POS] >= v[GNL_RLEN] && v[GNL_BUF_POS] > 0 && v[GNL_RLEN] > 0)
		flags[GNL_EXIT] = 1;
	while (1)
	{
		v[GNL_RES] = gnl_loop_alg(buf, &line, v, flags);
		if (v[GNL_RES] == GNL_RET)
			return (line);
		else if (v[GNL_RES] == GNL_BREAK)
			break ;
		else if (v[GNL_RES] == GNL_CONT)
			continue ;
	}
	if (v[GNL_ERR])
		*err = 1;
	gnl_clear_func_state(&line, v, flags);
	return (NULL);
}

/* When we return BREAK it means malloc() error */
int	gnl_loop_alg(char *buf, char **line, long long *v, int *flags)
{
	int	res;

	res = gnl_init(buf, line, v, flags);
	if (res == GNL_RET)
		return (GNL_RET);
	else if (res == GNL_BREAK)
		return (GNL_BREAK);
	if (gnl_get_chunk(buf, line, v, flags) == GNL_BREAK)
		return (GNL_BREAK);
	gnl_check_reaching_end(v, flags);
	if (buf[v[GNL_BUF_POS]] == '\n')
	{
		gnl_process_new_line(buf, line, v, flags);
		return (GNL_RET);
	}
	else
	{
		if (gnl_process_end_chunk(line, v, flags))
			return (GNL_RET);
		return (GNL_CONT);
	}
	return (GNL_NORM);
}

/* It finds the first chunk of data in read buffer,
 * allocates memory for it and copies its content
 * into the `line` */
int	gnl_get_chunk(char *buf, char **line, long long *v, int *flags)
{
	v[GNL_I] = 0;
	while (buf[v[GNL_BUF_POS]] != '\n' && v[GNL_BUF_POS] < v[GNL_RLEN])
	{
		v[GNL_BUF_POS]++;
		v[GNL_I]++;
	}
	v[GNL_LINE_LEN] = v[GNL_I];
	v[GNL_LINE_POS] += v[GNL_LINE_LEN];
	if (gnl_alloc_mem(line, v, flags) == GNL_BREAK)
		return (GNL_BREAK);
	v[GNL_I] = 0;
	while (v[GNL_I] < v[GNL_LINE_LEN])
	{
		(*line)[v[GNL_LINE_POS] - v[GNL_LINE_LEN] + v[GNL_I]]
			= buf[v[GNL_BUF_POS] - v[GNL_LINE_LEN] + v[GNL_I]];
		v[GNL_I]++;
	}
	return (GNL_NORM);
}

void	gnl_process_new_line(char *buf, char **line, long long *v, int *flags)
{
	(*line)[v[GNL_LINE_POS] - v[GNL_LINE_LEN] + v[GNL_I]] = '\n';
	(*line)[v[GNL_LINE_POS] - v[GNL_LINE_LEN] + v[GNL_I] + 1] = '\0';
	if (v[GNL_BUF_POS] < v[GNL_RLEN] - 1 && !flags[GNL_END])
		v[GNL_BUF_POS]++;
	v[GNL_LINE_POS] = 0;
	flags[GNL_ALLOC] = 0;
	flags[GNL_READ] = 0;
	flags[GNL_END] = 0;
	if (v[GNL_BUF_POS] == v[GNL_RLEN] - 1 && buf[v[GNL_BUF_POS]] == '\n')
	{
		flags[GNL_READ] = 1;
		if (!flags[GNL_AGAIN] && buf[v[GNL_BUF_POS] - 1] == '\n')
		{
			flags[GNL_AGAIN] = 1;
			flags[GNL_READ] = 0;
		}
	}
}

int	gnl_process_end_chunk(char **line, long long *v, int *flags)
{
	flags[GNL_ALLOC] = 1;
	flags[GNL_READ] = 1;
	flags[GNL_END] = 0;
	if (v[GNL_RLEN] < GNL_BUFFER_SIZE)
	{
		(*line)[v[GNL_LINE_POS] - v[GNL_LINE_LEN] + v[GNL_I]] = '\0';
		flags[GNL_ALLOC] = 0;
		v[GNL_LINE_POS] = 0;
		return (GNL_RET);
	}
	return (GNL_NORM);
}
