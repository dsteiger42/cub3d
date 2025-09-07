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


void print_map(char **map, int line_count)
{
    int i;

    if (!map || line_count <= 0)
        return;

    i = 0;
    printf("=== MAP ===\n");
    while (i < line_count)
    {
        printf("%s", map[i]);
        i++;
    }
}

void free_map(char **map, int line_count)
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
    printf("Floor color: R=%d G=%d B=%d\n",
           cfg->floor[0], cfg->floor[1], cfg->floor[2]);
    printf("Ceiling color: R=%d G=%d B=%d\n",
           cfg->ceiling[0], cfg->ceiling[1], cfg->ceiling[2]);
    printf("=================\n");
}

void    free_config_map(t_config *config_map)
{
    if (!config_map)
        return;

    free(config_map->no);
    free(config_map->so);
    free(config_map->we);
    free(config_map->ea);
    free(config_map);
}

void free_data(t_data *data)
{
    if (!data)
        return;
    if (data->pmap) 
    {
        free_map(data->pmap->map, data->pmap->line_count);
        free_map(data->pmap->map2, data->pmap->line_count);
        free(data->pmap);
        data->pmap = NULL;
    }
    if (data->config_map)
        free_config_map(data->config_map);
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    if (data->mlx_win)
        mlx_destroy_window(data->mlx, data->mlx_win);
    if (data->mlx) 
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
}

