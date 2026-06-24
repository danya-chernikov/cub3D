/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 10:02:17 by dchernik          #+#    #+#             */
/*   Updated: 2026/06/24 16:28:53 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

#include <sys/time.h>

double	game_time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

/* Updates the time difference between the
 * current frame and the previous frame.
 * On the first frame, `last_time` is still
 * zero, so `delta_time` is set to zero.
 * After that, `delta_time` stores the real
 * elapsed time in seconds. The value is
 * clamped to avoid very large movement (like
 * a sudden jump to another part of the map)
 * steps after a pause, resize, breakpoint,
 * system freeze and etc. */
void	game_update_delta_time(t_cube *cube)
{
	double	now;

	now = game_time_now();
	if (cube->last_time == 0.0)
		cube->delta_time = 0.0;
	else
		cube->delta_time = now - cube->last_time;
	cube->last_time = now;
	if (cube->delta_time > 0.05)
		cube->delta_time = 0.05;
}
