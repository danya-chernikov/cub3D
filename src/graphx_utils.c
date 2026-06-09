/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 15:49:53 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/08 16:20:29 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphx.h"

#include <stdio.h>
#include <stdlib.h>

static void		swap(double *a, double *b);
static size_t	partition(double *arr, int low, int high);

void	graphx_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	put_pixel_safe(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x < 0 || y < 0)
		return ;
	if ((uint32_t)x >= img->width || (uint32_t)y >= img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

void	quick_sort_doubles(double *arr, int low, int high)
{
	int	pivot_ind;

	if (low < high)
	{
		pivot_ind = partition(arr, low, high);
		quick_sort_doubles(arr, low, pivot_ind - 1);
		quick_sort_doubles(arr, pivot_ind + 1, high);
	}
}

static void	swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static size_t	partition(double *arr, int low, int high)
{
	double	pivot;
	int		i;
	int		j;

	j = low;
	i = low - 1;
	pivot = arr[high];
	while (j <= high - 1)
	{
		if (arr[j] < pivot)
		{
			++i;
			swap(&arr[i], &arr[j]);
		}
		++j;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}
