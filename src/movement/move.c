/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:46:43 by samuel            #+#    #+#             */
/*   Updated: 2025/09/13 23:46:53 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x + data->player.dir_x * MOVE_SPEED;
	ny = data->player.pos_y + data->player.dir_y * MOVE_SPEED;
	if (can_move_x(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	if (can_move_y(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}

void	move_backward(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x - data->player.dir_x * MOVE_SPEED;
	ny = data->player.pos_y - data->player.dir_y * MOVE_SPEED;
	if (can_move_x(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	if (can_move_y(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}

void	move_left(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x - data->player.plane_x * MOVE_SPEED;
	ny = data->player.pos_y - data->player.plane_y * MOVE_SPEED;
	if (can_move_x(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	if (can_move_y(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}

void	move_right(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x + data->player.plane_x * MOVE_SPEED;
	ny = data->player.pos_y + data->player.plane_y * MOVE_SPEED;
	if (can_move_x(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	if (can_move_y(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}
