/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:53:43 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/29 18:36:13 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int valid_map_name(char *file)
{
	int len;

	if (!file)
		return (err_msg("Invalid pointer\n", 1), -1);	
	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - 4], ".cub", 4) != 0)
		return (err_msg("Map is not a .cub file\n", 1), -1);
	return (0);
}


int validfd(t_map *map, char *file)
{
	int fd;
	char *line;

	map->line_count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (err_msg("Invalid fd\n", 1), -1);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			map->line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (0);
}

static void	set_player_dir_plane(t_player *player, char c)
{
	if (c == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (c == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (c == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

/* trata a posição inicial do jogador */
static int	handle_player_start(t_data *data, char c, int x, int y)
{
	if (!data || !ft_strchr("NSEW", c))
		return (0);
	data->player.players++;
	if (data->player.players > 1)
		return (err_msg("Multiple start positions\n", 1), -1);
	data->player.pos_x = x + 0.5;
	data->player.pos_y = y + 0.5;
	set_player_dir_plane(&data->player, c);
	return (0);
}

int	valid_map(t_data *data)
{
	int	y;
	int	x;
	char	c;

	if (!data || !data->pmap || !data->pmap->map)
		return (err_msg("Map not loaded\n", 1), -1);
	y = 0;
	while (y < data->pmap->line_count)
	{
		x = 0;
		while (data->pmap->map[y][x])
		{
			c = data->pmap->map[y][x];
			if (!ft_strchr("01NSEW \t\v\r\f\n", c))
				return (err_msg("Invalid character in map\n", 1), -1);
			if (handle_player_start(data, c, x, y) == -1)
				return (-1);
			x++;
		}
		y++;
	}
	if (data->player.players != 1)
		return (err_msg("No start position found\n", 1), -1);
	return (0);
}

