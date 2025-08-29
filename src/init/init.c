/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:06:43 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/29 15:48:08 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int init_map(t_map *pmap)
{
	if (!pmap)
		return -1;
	pmap->map = NULL;
	pmap->map2 = NULL;	
	pmap->line_count = 0;
	return 0;
}

int init_data_structures(t_data *data)
{
	data->pmap = malloc(sizeof(t_map));
	if (!data->pmap)
	{
		write(2, "\033[91mERROR\nMemory allocation failed\n", 36);
		return 1;
	}

	if (init_map(data->pmap) == -1)
	{
		free(data->pmap);
		write(2, "\033[91mERROR\nMap initialization failed\n", 36);
		return 1;
	}

	return 0;
}
