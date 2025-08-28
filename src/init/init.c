/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:06:43 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/28 19:21:17 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int init_map(t_map *map)
{
	if (!map)
		return -1;
	map->map = NULL;
	map->line_count = 0;
	return 0;
}

int init_data_structures(t_data *data)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
	{
		write(2, "\033[91mERROR\nMemory allocation failed\n", 36);
		return 1;
	}

	if (init_map(data->map) == -1)
	{
		free(data->map);
		write(2, "\033[91mERROR\nMap initialization failed\n", 36);
		return 1;
	}

	return 0;
}
