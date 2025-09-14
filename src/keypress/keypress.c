/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 23:19:16 by samuel            #+#    #+#             */
/*   Updated: 2025/09/14 23:19:53 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == W)
		data->keys.w = 1;
	else if (keycode == S)
		data->keys.s = 1;
	else if (keycode == A)
		data->keys.a = 1;
	else if (keycode == D)
		data->keys.d = 1;
	else if (keycode == LEFT_ARROW)
		data->keys.left = 1;
	else if (keycode == RIGHT_ARROW)
		data->keys.right = 1;
	else if (keycode == ESC)
		mlx_loop_end(data->mlx);
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == W)
		data->keys.w = 0;
	else if (keycode == S)
		data->keys.s = 0;
	else if (keycode == A)
		data->keys.a = 0;
	else if (keycode == D)
		data->keys.d = 0;
	else if (keycode == LEFT_ARROW)
		data->keys.left = 0;
	else if (keycode == RIGHT_ARROW)
		data->keys.right = 0;
	return (0);
}

int	handle_close(t_data *data)
{
	if (!data)
		exit(0);
	if (data->mlx)
		mlx_loop_end(data->mlx);
	return (0);
}
