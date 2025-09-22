/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 23:14:29 by samuel            #+#    #+#             */
/*   Updated: 2025/09/14 23:14:30 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	init_mouse(int x, int y, int *old_x, int *old_y)
{
	if (*old_x == -1 || *old_y == -1)
	{
		*old_x = x;
		*old_y = y;
		return (1);
	}
	return (0);
}

static int	handle_delta(int x, int old_x, t_data *data)
{
	int	delta_x;

	delta_x = x - old_x;
	if (delta_x > data->screen_h / 2 || delta_x < -data->screen_h / 2)
		return (1);
	if (delta_x != 0)
		rotate_player(data, delta_x * MOUSE_SENSITIVITY);
	return (0);
}

static int	check_horizontal_wrap(int x, int y, t_data *data, int *ignore_event)
{
	int	new_x;

	if (x > data->screen_h - DIST_EDGE_MOUSE_WRAP - 5
		|| x < DIST_EDGE_MOUSE_WRAP + 5)
	{
		if (x > data->screen_h - DIST_EDGE_MOUSE_WRAP - 5)
			new_x = DIST_EDGE_MOUSE_WRAP + 5;
		else
			new_x = data->screen_h - DIST_EDGE_MOUSE_WRAP - 5;
		mlx_mouse_move(data->mlx, data->mlx_win, new_x, y);
		*ignore_event = 1;
		return (1);
	}
	return (0);
}

static int	check_vertical_wrap(int old_x, int y, t_data *data,
		int *ignore_event)
{
	int	new_y;

	if (y > data->screen_h - DIST_EDGE_MOUSE_WRAP - 5
		|| y < DIST_EDGE_MOUSE_WRAP + 5)
	{
		if (y > data->screen_h - DIST_EDGE_MOUSE_WRAP - 5)
			new_y = DIST_EDGE_MOUSE_WRAP + 5;
		else
			new_y = data->screen_h - DIST_EDGE_MOUSE_WRAP - 5;
		mlx_mouse_move(data->mlx, data->mlx_win, old_x, new_y);
		*ignore_event = 1;
		return (1);
	}
	return (0);
}

int	handle_mouse(int x, int y, t_data *data)
{
	static int	old_x = -1;
	static int	old_y = -1;
	static int	ignore_event = 0;

	if (init_mouse(x, y, &old_x, &old_y))
		return (0);
	if (ignore_event)
	{
		ignore_event = 0;
		return (0);
	}
	if (handle_delta(x, old_x, data))
	{
		old_x = x;
		old_y = y;
		return (0);
	}
	old_x = x;
	old_y = y;
	if (check_horizontal_wrap(x, y, data, &ignore_event))
		return (0);
	check_vertical_wrap(old_x, y, data, &ignore_event);
	return (0);
}
