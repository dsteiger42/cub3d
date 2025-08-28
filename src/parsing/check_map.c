/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:53:43 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/28 18:28:15 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int skip_spaces(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (0);
	return (1);
}

int valid_map_name(char *av)
{
	int len;

	if (!av)
	{
		write(2, "\033[91mERROR\nInvalid pointer\n", 28);
		return (-1);
	}
	len = strlen(av); // mudar pra ft_strlen
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

int valid_map(char *file)
{
	int fd;
	char *line;
	int i;
	char c;
	int erro = 0;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2, "\033[91mERROR\nInvalid fd\n", 23);
		return (-1);
	}
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (!skip_spaces(line[i]))
			{
				i++;
				continue;
			}
			c = line[i++];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				erro++;
			else if (c != '0' && c != '1' && c != '\n')
			{
				free(line);
				write(2, "\033[91mERROR\nInvalid character\n", 30);
				return (-1);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	if (erro != 1)
	{
		write(2, "\033[91mERROR\nInvalid character\n", 30);
		return (-1);
	}
	return (0);
}
