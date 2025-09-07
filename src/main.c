/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:58:27 by dsteiger          #+#    #+#             */
/*   Updated: 2025/09/04 18:25:16 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int open_and_check(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (err_msg("Texture file not found\n", 1), -1);
    close(fd);
    return (0);
}

int valid_textures(t_config *config_map)
{
	if (!config_map->no || !config_map->so ||
		!config_map->we || !config_map->ea)
		return (err_msg("Missing texture\n", 1), -1);

	if (open_and_check(config_map->no) == -1)
		return (-1);
	if (open_and_check(config_map->so) == -1)
		return (-1);
	if (open_and_check(config_map->we) == -1)
		return (-1);
	if (open_and_check(config_map->ea) == -1)
		return (-1);
	return (0);
}

int init_and_validate(t_data *data, char *file)
{
    if (!data || !file)
		return (1);
	if(init_data_structures(data))
		return (1);
	if (valid_map_name(file))
        return (1);
	if (validfd(data->pmap, file))
		return (1);
	if (parse_file(data, file))
		return (1);
	if(valid_textures(data->config_map))
		return (1);
    if (valid_map(data))
    	return (1);
    if (create_map(data))
        return (1);
    return 0;
}

int main(int ac, char *av[])
{
	t_data data;

	if (ac != 2)
		return (err_msg("Wrong number of args\n", 1)), -1;
	if(init_and_validate(&data, av[1]))
		return (free_data(&data), -1);
	print_map(data.pmap->map, data.pmap->line_count);
	init_mlx(&data);
	free_data(&data);
	return (0);
}
