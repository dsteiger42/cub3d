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

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
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

void print_config_map(t_config *cfg)
{
    if (!cfg)
        return;

    printf("=== CONFIG MAP ===\n");
    printf("NO texture: %s\n", cfg->no ? cfg->no : "(null)");
    printf("SO texture: %s\n", cfg->so ? cfg->so : "(null)");
    printf("WE texture: %s\n", cfg->we ? cfg->we : "(null)");
    printf("EA texture: %s\n", cfg->ea ? cfg->ea : "(null)");
    printf("Floor color: R=%d G=%d B=%d (got_f=%d)\n",
           cfg->floor[0], cfg->floor[1], cfg->floor[2], cfg->got_f);
    printf("Ceiling color: R=%d G=%d B=%d (got_c=%d)\n",
           cfg->ceiling[0], cfg->ceiling[1], cfg->ceiling[2], cfg->got_c);
    printf("=================\n");
}

void free_data(t_data *data)
{
    if (!data || !data->pmap)
        return;

    free_map(data->pmap->map, data->pmap->line_count);
    data->pmap->map = NULL;

    free_map2(data->pmap->map2, data->pmap->line_count);
    data->pmap->map2 = NULL;

	//free_mlx(data);

    free(data->pmap);
    data->pmap = NULL;
}
