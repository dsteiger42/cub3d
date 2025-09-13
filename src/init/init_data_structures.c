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

int	init_data_structures(t_data *data)
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
	if (init_texture(&data->textures[0]) == -1
		|| init_texture(&data->textures[1]) == -1
		|| init_texture(&data->textures[2]) == -1
		|| init_texture(&data->textures[3]) == -1)
		return (free(data->pmap), err_msg("Texture init failed\n", 1), -1);
	ft_bzero(&data->keys, sizeof(t_keys));
	return (0);
}