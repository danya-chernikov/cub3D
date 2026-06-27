/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeestev <adeestev@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 11:29:50 by adeestev          #+#    #+#             */
/*   Updated: 2026/06/26 12:01:31 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
advances past any spaces, then convert string into an integer and enforces
that the result falls within the standard 0-255 RGB range
*/
static int	get_rgb_val(char **str, int *val)
{
	int	num;
	int	digits;

	num = 0;
	digits = 0;
	*str = skip_spaces(*str);
	while (ft_isdigit(**str))
	{
		num = num * 10 + (**str - '0');
		digits++;
		(*str)++;
	}
	if (digits == 0 || num < 0 || num > 255)
		return (0);
	*str = skip_spaces(*str);
	*val = num;
	return (1);
}

/*
validates syntax and uses left bitshifting to pack the colors into
a single 32-bit uint
*/
int	parse_color(char *line, uint32_t *color)
{
	int	r;
	int	g;
	int	b;

	if (!get_rgb_val(&line, &r) || *line != ',')
		return (print_error(MAP_INV_COL_RANGE_ERR), 0);
	line++;
	if (!get_rgb_val(&line, &g) || *line != ',')
		return (print_error(MAP_INV_COL_RANGE_ERR), 0);
	line++;
	if (!get_rgb_val(&line, &b))
		return (print_error(MAP_INV_COL_RANGE_ERR), 0);
	if (*line != '\n' && *line != '\0' && *line != '\r')
		return (print_error(MAP_INV_COL_RANGE_ERR), 0);
	*color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	return (1);
}
