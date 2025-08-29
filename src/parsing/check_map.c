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

int valid_map_name(char *av)
{
	int len;

	if (!av)
	{
		write(2, "\033[91mERROR\nInvalid pointer\n", 28);
		return (-1);
	}
	len = ft_strlen(av);
	if (len < 4 || ft_strncmp(&av[len - 4], ".cub", 4) != 0)
	{
		write(2, "\033[91mERROR\nMap is not a .cub file\n", 35);
		return (-1);
	}
	return (0);
}
int validfd(t_map *map, char *file)
{
	int fd;
	char *line;

	map->line_count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2, "\033[91mERROR\nInvalid fd\n", 23);
		return (-1);
	}
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
            //if (!ft_strchr("01NSEW \t\v\r\f\n", c)) outra maneira de escrever
            if (c != '0' && c != '1' && c != ' ' && c != '\t' && c != '\v' && c != '\r' && c != '\f' && c != '\n' &&
				c != 'N' && c != 'S' && c != 'E' && c != 'W' )
            {
                free(line);
                write(2, "\033[91mERROR\nInvalid character\n", 30);
                close(fd);
                return -1;
            }
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                start_count++;
                data->player.pos_x = pos_x;
                data->player.pos_y = pos_y;
                if (start_count > 1)
                {
                    free(line);
                    write(2, "\033[91mERROR\nMultiple start positions\n", 36);
                    close(fd);
                    return -1;
                }
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
