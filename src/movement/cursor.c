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

int	handle_mouse(int x, int y, t_data *data)
{
	static int	old_x = -1;
	static int	old_y = -1;
	static int	ignore_event = 0;
	int			delta_x;
	int			new_x;
	int			new_y;

	if (old_x == -1 || old_y == -1)
	{
		old_x = x;
		old_y = y;
		return (0);
	}
	if (ignore_event)
	{
		ignore_event = 0;
		return (0);
	}
	delta_x = x - old_x;
	if (delta_x > data->screen_h / 2 || delta_x < -data->screen_h / 2)
	{
		old_x = x;
		old_y = y;
		return (0);
	}
	if (delta_x != 0)
		rotate_player(data, delta_x * MOUSE_SENSITIVITY);
	old_x = x;
	old_y = y;
	if (x > data->screen_h - DIST_EDGE_MOUSE_WRAP - 5 || x < DIST_EDGE_MOUSE_WRAP
		+ 5)
	{
		new_x = (x > data->screen_h - DIST_EDGE_MOUSE_WRAP
				- 5) ? DIST_EDGE_MOUSE_WRAP + 5 : data->screen_h
			- DIST_EDGE_MOUSE_WRAP - 5;
		mlx_mouse_move(data->mlx, data->mlx_win, new_x, y);
		ignore_event = 1;
	}
	if (y > data->screen_h - DIST_EDGE_MOUSE_WRAP - 5 || y < DIST_EDGE_MOUSE_WRAP
		+ 5)
	{
		new_y = (y > data->screen_h - DIST_EDGE_MOUSE_WRAP
				- 5) ? DIST_EDGE_MOUSE_WRAP + 5 : data->screen_h
			- DIST_EDGE_MOUSE_WRAP - 5;
		mlx_mouse_move(data->mlx, data->mlx_win, old_x, new_y);
		ignore_event = 1;
	}
	return (0);
}
