/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:34:17 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/29 16:36:47 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void print_map(t_data *data)
{
    int i;

    if (!data || !data->pmap || !data->pmap->map)
        return;

    i = 0;
    while (i < data->pmap->line_count)
    {
        printf("%s", data->pmap->map2[i]);
        i++;
    }
}

void free_data(t_data *data)
{
    int i;

    if (!data || !data->pmap)
        return;
    if (data->pmap->map)
    {
        i = 0;
        while (i < data->pmap->line_count)
        {
            free(data->pmap->map[i]);
            i++;
        }
        free(data->pmap->map);
        data->pmap->map = NULL;
    }
    if (data->pmap->map2)
    {
        i = 0;
        while (i < data->pmap->line_count)
        {
            free(data->pmap->map2[i]);
            i++;
        }
        free(data->pmap->map2);
        data->pmap->map2 = NULL;
    }
    free(data->pmap);
    data->pmap = NULL;
}
