/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:41:26 by dchernik          #+#    #+#             */
/*   Updated: 2024/10/11 16:54:03 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*itoa_alloc(int size);
static void	itoa_sign_check(char *buf, int n, int *i);
static char	*itoa_reverse(char *str, int slen);
static int	count_digits(int n);

char	*ft_itoa(int n)
{
	int		i;
	long	num;
	char	*buf;
	char	dnum;

	i = 0;
	dnum = 0;
	num = n;
	if (n < 0)
	{
		num = -num;
		dnum = 1;
	}
	buf = itoa_alloc(dnum + count_digits(n) + 1);
	if (buf == NULL)
		return (NULL);
	while (num != 0)
	{
		buf[i] = (num % 10) + '0';
		num /= 10;
		i++;
	}
	itoa_sign_check(buf, n, &i);
	buf[i] = '\0';
	return (itoa_reverse(buf, i));
}

static int	count_digits(int n)
{
	int	num;

	num = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		num++;
	}
	return (num);
}

static char	*itoa_alloc(int size)
{
	char	*buf;

	buf = (char *)malloc(size * sizeof(char));
	if (buf == NULL)
		return (NULL);
	return (buf);
}

static void	itoa_sign_check(char *buf, int n, int *i)
{
	if (n == 0)
	{
		buf[0] = '0';
		(*i) = 1;
	}
	else if (n < 0)
	{
		buf[*i] = '-';
		(*i)++;
	}
}

static char	*itoa_reverse(char *str, int slen)
{
	int	q;
	int	tmp;

	q = 0;
	while (q < slen / 2)
	{
		tmp = str[q];
		str[q] = str[slen - q - 1];
		str[slen - q - 1] = tmp;
		q++;
	}
	return (str);
}
