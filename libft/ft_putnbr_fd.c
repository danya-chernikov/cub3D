/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:42:14 by dchernik          #+#    #+#             */
/*   Updated: 2024/10/11 18:19:25 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	putnbr_sign_check(char *buf, int n, int *i);
static int	get_intmin(void);

void	ft_putnbr_fd(int n, int fd)
{
	char	buf[21];
	int		i;
	int		num;

	num = n;
	if (n == get_intmin())
		num++;
	if (n < 0)
		num = -1 * num;
	i = 0;
	buf[0] = '0';
	while (num != 0)
	{
		buf[i] = (num % 10) + '0';
		num /= 10;
		i++;
	}
	putnbr_sign_check(buf, n, &i);
	while (i > 0)
	{
		write(fd, &buf[i - 1], 1);
		i--;
	}
}

static int	get_intmin(void)
{
	int	int_min;

	int_min = 1;
	while (int_min > 0)
		int_min <<= 1;
	return (int_min);
}

static void	putnbr_sign_check(char *buf, int n, int *i)
{
	if (n == get_intmin())
		buf[0] = -1 * (n % 10) + '0';
	if (n < 0)
	{
		buf[*i] = '-';
		(*i)++;
	}
	else if (n == 0)
		(*i)++;
}
