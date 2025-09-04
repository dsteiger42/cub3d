/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:06:43 by scarlos-          #+#    #+#             */
/*   Updated: 2025/09/04 18:38:11 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int close_window(t_data *data)
{
	if (!data)
		exit(0);
	if (data->mlx_win && data->mlx)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
}
int	ft_keyhook(int keycode, t_data *data)
{
	/*if (keycode == W)
		ft_move_forward(data);
	else if (keycode == S)
		ft_move_backward(data);
	else if (keycode == LEFT_ARROW)
		ft_turn_left(data);
	else if (keycode == RIGHT_ARROW)
		ft_turn_right(data);*/
	if (keycode == ESC)
		close_window(data);
	return (0);
}


void init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(1);
	data->mlx_win = mlx_new_window(data->mlx, 960, 720, "cub3D");
	if (!data->mlx_win)
		exit(1);

	data->img = mlx_new_image(data->mlx, 960, 720);


	mlx_hook(data->mlx_win, 2, 1L<<0, ft_keyhook, data); // teclado
	mlx_hook(data->mlx_win, 17, 0, close_window, data);   // X da janela


	mlx_loop(data->mlx);
}


int init_player(t_player *player)
{
	if (!player)
		return (-1);
	player->pos_x = -1;
	player->pos_y = -1;
	return (0);
}

int init_map(t_map *pmap)
{
	if (!pmap)
		return -1;
	pmap->map = NULL;
	pmap->map2 = NULL;
	pmap->line_count = 0;
	return (0);
}

int init_data_structures(t_data *data)
{
    if (!data)
        return -1;

    ft_bzero(data, sizeof(t_data));

    data->pmap = malloc(sizeof(t_map));
    if (!data->pmap)
        return (err_msg("Memory allocation failed\n", 1), -1);
    data->pmap->map = NULL;
    data->pmap->map2 = NULL;
    data->pmap->line_count = 0;
    if (init_player(&data->player) == -1)
		return (err_msg("Player initialization failed\n", 1), -1);
    if (init_map(data->pmap) == -1)
		return (err_msg("Map initialization failed\n", 1), -1);
    return 0;
}
