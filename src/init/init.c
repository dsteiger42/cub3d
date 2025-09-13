/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:06:43 by scarlos-          #+#    #+#             */
/*   Updated: 2025/09/14 00:05:42 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	can_move_x(t_data *data, double nx, double y)
{
	if (data->pmap->map[(int)(y + PLAYER_RADIUS)][(int)(nx
			+ PLAYER_RADIUS)] == '1')
		return (0);
	if (data->pmap->map[(int)(y - PLAYER_RADIUS)][(int)(nx
			+ PLAYER_RADIUS)] == '1')
		return (0);
	if (data->pmap->map[(int)(y + PLAYER_RADIUS)][(int)(nx
			- PLAYER_RADIUS)] == '1')
		return (0);
	if (data->pmap->map[(int)(y - PLAYER_RADIUS)][(int)(nx
			- PLAYER_RADIUS)] == '1')
		return (0);
	return (1);
}

int	can_move_y(t_data *data, double x, double ny)
{
	if (data->pmap->map[(int)(ny + PLAYER_RADIUS)][(int)(x
			+ PLAYER_RADIUS)] == '1')
		return (0);
	if (data->pmap->map[(int)(ny - PLAYER_RADIUS)][(int)(x
			+ PLAYER_RADIUS)] == '1')
		return (0);
	if (data->pmap->map[(int)(ny + PLAYER_RADIUS)][(int)(x
			- PLAYER_RADIUS)] == '1')
		return (0);
	if (data->pmap->map[(int)(ny - PLAYER_RADIUS)][(int)(x
			- PLAYER_RADIUS)] == '1')
		return (0);
	return (1);
}

int	game_loop(t_data *data)
{
	if (data->keys.w)
		move_forward(data);
	if (data->keys.s)
		move_backward(data);
	if (data->keys.a)
		move_left(data);
	if (data->keys.d)
		move_right(data);
	if (data->keys.left)
		rotate_left(data);
	if (data->keys.right)
		rotate_right(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

void	get_screen_size(t_data *data)
{
	mlx_get_screen_size(data->mlx, &data->screen_w, &data->screen_h);
	data->screen_w = (int)(data->screen_w * 0.8);
	data->screen_h = (int)(data->screen_h * 0.8);
	if (data->screen_w > 1920)
		data->screen_w = 1920;
	if (data->screen_h > 1080)
		data->screen_h = 1080;
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		clean_exit(data, err_msg("mlx: Could not start mlx\n", 1));
	get_screen_size(data);
	if (init_textures(data) == -1)
		clean_exit(data, err_msg("Textures init failed\n", 1));
	data->mlx_win = mlx_new_window(data->mlx, data->screen_w,
			data->screen_h, "cub3D");
	if (!data->mlx_win)
		clean_exit(data, err_msg("mlx_win: Could not open window\n", 1));
	data->img = mlx_new_image(data->mlx, data->screen_w, data->screen_h);
	if (!data->img)
		clean_exit(data, err_msg("img: Could not create new image\n", 1));
	mlx_hook(data->mlx_win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->mlx_win, 17, 0, handle_close, data);
	mlx_hook(data->mlx_win, 6, 1L << 6, handle_mouse, data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
}
