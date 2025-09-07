/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:06:43 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/29 19:15:11 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int handle_close(t_data *data)
{
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    if (data->mlx_win)
        mlx_destroy_window(data->mlx, data->mlx_win);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    free_data(data);
    return (0);
}


int handle_keypress(int keycode, t_data *data)
{
    if (keycode == ESC)
    {
        mlx_destroy_window(data->mlx, data->mlx_win);
        exit(0);
    }
    else if (keycode == W)
        printf("Move forward (W)\n");
    else if (keycode == S)
        printf("Move backward (S)\n");
    else if (keycode == A)
        printf("Move left (A)\n");
    else if (keycode == D)
        printf("Move right (D)\n");
    else if (keycode == LEFT_ARROW)
        printf("Rotate left (←)\n");
    else if (keycode == RIGTH_ARROW)
        printf("Rotate right (→)\n");
    return (0);
}


void init_mlx(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        clean_exit(data, err_msg("mlx: Could not start mlx\n", 1));
    data->mlx_win = mlx_new_window(data->mlx, 960, 720, "cub3D");
    if (!data->mlx_win)
        clean_exit(data, err_msg("mlx_win: Could not open mlx_window\n", 1));
    data->img = mlx_new_image(data->mlx, 960, 720);
    if (!data->img)
        clean_exit(data, err_msg("img: Could not create new image\n", 1));      
    mlx_hook(data->mlx_win, 2, 1L<<0, handle_keypress, data);  // evento de tecla
    mlx_hook(data->mlx_win, 17, 0, handle_close, data);  // evento "X" da janela 
    mlx_loop(data->mlx);
}

int init_player(t_player *player)
{
	if (!player)
		return (-1);
	player->players = 0;
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

int init_config_map(t_config **config_map)
{
    if (!config_map)
        return (-1);
    *config_map = malloc(sizeof(t_config));
    if (!*config_map)
        return (err_msg("Memory allocation failed for config_map\n", 1), -1);
    (*config_map)->no = NULL;
	(*config_map)->so = NULL;
	(*config_map)->we = NULL;
	(*config_map)->ea = NULL;
	(*config_map)->floor[0] = 0;
	(*config_map)->ceiling[0] = 0;
    return 0;
}

int init_data_structures(t_data *data)
{
    if (!data)
        return (-1);

    data->mlx = NULL;
    data->mlx_win = NULL;

    data->pmap = malloc(sizeof(t_map));
    if (!data->pmap)
        return (err_msg("Memory allocation failed\n", 1), -1);
    if (init_player(&data->player) == -1)
        return (free(data->pmap), err_msg("Player init failed\n", 1), -1);
    if (init_map(data->pmap) == -1)
        return (free(data->pmap), err_msg("Map init failed\n", 1), -1);

    if (init_config_map(&data->config_map) == -1)
    {
        free(data->pmap);
        return (-1);
    }

    return 0;
}
