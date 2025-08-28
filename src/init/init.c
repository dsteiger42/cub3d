/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:06:43 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/28 18:08:20 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_data(t_data *data)
{
	data->map = NULL;
}

void init_map(t_map *map)
{
	map->map = NULL;
	map->line_count = 0;
}
