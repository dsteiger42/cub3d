/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:53:43 by scarlos-          #+#    #+#             */
/*   Updated: 2025/09/04 18:33:09 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int valid_map_name(char *av)
{
	int len;

	len = ft_strlen(av);
	if (!av)
		return (err_msg("Invalid pointer\n", 1), -1);
	if (len < 4 || ft_strncmp(&av[len - 4], ".cub", 4) != 0)
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
static int	handle_player_start(t_data *data, char c, int x, int y, int *count)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*count)++;
		data->player.pos_x = x;
		data->player.pos_y = y;
		if (*count > 1)
		{
			write(2, "\033[91mERROR\nMultipleasdaad start positions\n", 36);
			return (-1);
		}
	}
	return (0);
}

int valid_map(t_data *data, char *file)
{
    int fd;
    char *line;
    int pos_y = 0;
    int pos_x;
    char c;
    int start_count = 0;

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        write(2, "\033[91mERROR\nInvalid fd\n", 23);
        return -1;
    }
    line = get_next_line(fd);
    while (line)
    {
        pos_x = 0;
        while (line[pos_x])
        {
            c = line[pos_x];
            /(!ft_strchr("01NSEW \t\v\r\f\n", c))
                return (free(line), close(fd),
					err_msg("Invalid character\n", 1), -1);
			if (handle_player_start(data, line[pos_x], pos_x, pos_y, &start_count) == -1)
				return (free(line), close(fd), -1);
            pos_x++;
        }
        free(line);
        pos_y++;
        line = get_next_line(fd);
    }
    close(fd);
    return 0;
}
