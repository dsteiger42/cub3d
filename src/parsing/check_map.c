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

static int	handle_player_start(t_data *data, char c, int x, int y)
{
	if (ft_strchr("NSEW", c))
	{
		data->player.players++;
		data->player.pos_x = x;
		data->player.pos_y = y;
		if (data->player.players > 1)
			return (err_msg("Multiple start positions\n", 1), -1);
	}
	return (0);
}
int valid_map(t_data *data, char *file)
{
    int fd;
    char *line;
    int pos_y;
    int pos_x;
    char c;

	pos_y = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
    	return (err_msg("Invalid fd\n", 1), -1);
    line = get_next_line(fd);
    while (line)
    {
        pos_x = 0;
        while (line[pos_x])
        {
            c = line[pos_x];
            if (!ft_strchr("01NSEW \t\v\r\f\n", c))
			{
				free(line);
				close(fd);
				return (err_msg("Invalid character\n", 1), -1);
			}
			if(handle_player_start(data, line[pos_x], pos_x, pos_y) == -1)
			{
				free(line);
				close(fd);
				return (-1);
			}
            pos_x++;
        }
        free(line);
        pos_y++;
        line = get_next_line(fd);
    }
    close(fd);
    return 0;
}
