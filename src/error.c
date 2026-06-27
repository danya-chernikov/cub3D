/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:19:43 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/28 00:55:05 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"

#include <errno.h>
#include <unistd.h> /* for write() */

void	print_error(const char *msg)
{
	if (!msg)
		return ;
	if (!write_all(STDERR_FILENO, "Error\n", 6))
		return ;
	if (write_all(STDERR_FILENO, msg, ft_strlen(msg)))
		return ;
	write_all(STDERR_FILENO, "\n", 1);
}

int	write_all(int fd, const char *s, size_t len)
{
	ssize_t	written;

	while (len > 0)
	{
		written = write(fd, s, len);
		if (written < 0)
			return (COMMON_FAILURE);
		s += written;
		len -= written;
	}
	return (COMMON_SUCCESS);
}
