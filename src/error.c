/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:19:43 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/05 11:35:25 by adeestev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"

#include <errno.h>
#include <string.h> /* for strerror() */
#include <unistd.h> /* for write() */

/* Prints a system error message in the
 * terminal alongside a user-defined error
 * description stored in `msg` */
void	print_sys_error(const char *msg)
{
	int		saved_errno;
	char	buf[ERR_BUF_SIZE];
	char	*err;

	if (!msg)
		return ;
	saved_errno = errno;
	err = strerror(saved_errno);
	ft_strlcpy(buf, "Error: ", ERR_BUF_SIZE);
	ft_strlcat(buf, msg, ERR_BUF_SIZE);
	ft_strlcat(buf, ": ", ERR_BUF_SIZE);
	ft_strlcat(buf, err, ERR_BUF_SIZE);
	ft_strlcat(buf, "\n", ERR_BUF_SIZE);
	write(STDERR_FILENO, buf, ft_strlen(buf));
}

/* Prints user-defined warning message
 * `msg` in the terminal */
void	print_warning(const char *msg)
{
	char	buf[WARN_BUF_SIZE];

	if (!msg)
		return ;
	ft_strlcpy(buf, "Warning: ", WARN_BUF_SIZE);
	ft_strlcat(buf, msg, WARN_BUF_SIZE);
	ft_strlcat(buf, "\n", WARN_BUF_SIZE);
	write(STDERR_FILENO, buf, ft_strlen(buf));
}

// Required by subject
void	print_error(const char *msg)
{
	if (!msg)
		return ;
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}
