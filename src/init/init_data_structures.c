/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_structures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 00:03:50 by samuel            #+#    #+#             */
/*   Updated: 2025/09/15 10:33:13 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_player(t_player *player)
{
	if (!player)
		return (-1);
	player->players = 0;
	player->pos_x = -1;
	player->pos_y = -1;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	return (0);
}

int	init_map(t_map *pmap)
{
	if (!pmap)
		return (-1);
	pmap->map = NULL;
	pmap->map2 = NULL;
	pmap->line_count = 0;
	pmap->no = NULL;
	pmap->so = NULL;
	pmap->we = NULL;
	pmap->ea = NULL;
	ft_bzero(pmap->floor, sizeof(pmap->floor));
	ft_bzero(pmap->ceiling, sizeof(pmap->ceiling));
	return (0);
}

void	init_img(t_img *img)
{
	if (!img)
		return ;
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

//inits map, player, textures and keys inside data
int	init_data_structures(t_data *data)
{
	if (!data)
		return (-1);
	ft_bzero(data, sizeof(t_data));
	data->pmap = malloc(sizeof(t_map));
	if (!data->pmap)
		return (err_msg("Memory allocation failed\n", 1), -1);
	if (init_player(&data->player) == -1 || init_map(data->pmap) == -1
		|| init_texture(&data->textures[0]) == -1
		|| init_texture(&data->textures[1]) == -1
		|| init_texture(&data->textures[2]) == -1
		|| init_texture(&data->textures[3]) == -1)
	{
		free(data->pmap);
		data->pmap = NULL;
		return (err_msg("Initialization failed\n", 1), -1);
	}
	init_img(data->img);
	ft_bzero(&data->keys, sizeof(t_keys));
	return (0);
}
