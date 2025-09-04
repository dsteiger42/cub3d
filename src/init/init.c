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

void init_mlx(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        clean_exit(data, err_msg("mlx: Could not start mlx\n", 1));
    data->mlx_win = mlx_new_window(data->mlx, 960, 720, "cub3D");
    if (!data->mlx_win)
        clean_exit(data, err_msg("mlx_win: Could not open mlx_window\n", 1));
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
		return (-1);

	data->mlx = NULL;
	data->mlx_win = NULL;
	data->pmap = malloc(sizeof(t_map));
	if (!data->pmap)
		return (err_msg("Memory allocation failed\n", 1), -1);
	if (init_player(&data->player) == -1)
	{
		free(data->pmap);
		return (err_msg("Player initialization failed\n", 1), -1);
	}
	if (init_map(data->pmap) == -1)
	{
		free(data->pmap);
		write(2, "\033[91mERROR\nMap initialization failed\n", 36);
		return (1);
	}
	return (0);
}
