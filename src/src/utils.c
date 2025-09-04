/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:34:17 by scarlos-          #+#    #+#             */
/*   Updated: 2025/09/04 18:08:55 by scarlos-         ###   ########.fr       */
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

static void free_map(char **map, int line_count)
{
    int i;

    if (!map || line_count <= 0)
        return;

    i = 0;
    while (i < line_count)
    {
        free(map[i]);
        i++;
    }
    free(map);
}

static void free_map2(char **map2, int line_count)
{
    int i;

    if (!map2 || line_count <= 0)
        return;

    i = 0;
    while (i < line_count)
    {
        free(map2[i]);
        i++;
    }
    free(map2);
}
void free_mlx(t_data *data)
{
    if (!data || !data->mlx)
        return;
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    if (data->mlx_win)
        mlx_destroy_window(data->mlx, data->mlx_win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    data->mlx = NULL;
}


void free_data(t_data *data)
{
    if (!data || !data->pmap)
        return;

    free_map(data->pmap->map, data->pmap->line_count);
    data->pmap->map = NULL;

    free_map2(data->pmap->map2, data->pmap->line_count);
    data->pmap->map2 = NULL;

	free_mlx(data);

    free(data->pmap);
    data->pmap = NULL;
}
