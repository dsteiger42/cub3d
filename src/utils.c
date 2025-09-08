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
void free_map_and_textures(t_map *pmap)
{
    int i;

    if (!pmap)
        return;

    // libera map
    if (pmap->map)
    {
        for (i = 0; i < pmap->line_count && pmap->map[i]; i++)
            free(pmap->map[i]);
        free(pmap->map);
        pmap->map = NULL;
    }

    // libera map2
    if (pmap->map2)
    {
        for (i = 0; i < pmap->line_count && pmap->map2[i]; i++)
            free(pmap->map2[i]);
        free(pmap->map2);
        pmap->map2 = NULL;
    }

    // libera texturas (paths)
    if (pmap->no) { free(pmap->no); pmap->no = NULL; }
    if (pmap->so) { free(pmap->so); pmap->so = NULL; }
    if (pmap->we) { free(pmap->we); pmap->we = NULL; }
    if (pmap->ea) { free(pmap->ea); pmap->ea = NULL; }

    pmap->line_count = 0;
}

void free_data(t_data *data)
{
    if (!data)
        return;

    // libera mapa e texturas
    if (data->pmap)
    {
        free_map_and_textures(data->pmap);
        free(data->pmap);
        data->pmap = NULL;
    }

    // libera imagem
    if (data->img && data->mlx)
    {
        mlx_destroy_image(data->mlx, data->img);
        data->img = NULL;
    }

    // libera janela
    if (data->mlx_win && data->mlx)
    {
        mlx_destroy_window(data->mlx, data->mlx_win);
        data->mlx_win = NULL;
    }

    // destrói display e libera struct mlx
    if (data->mlx)
    {
        free(data->mlx);
        data->mlx = NULL;
    }
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

void print_config_map(t_map *pmap)
{
    if (!pmap)
        return;

    printf("=== CONFIG MAP ===\n");
    printf("NO texture: %s\n", pmap->no ? pmap->no : "(null)");
    printf("SO texture: %s\n", pmap->so ? pmap->so : "(null)");
    printf("WE texture: %s\n", pmap->we ? pmap->we : "(null)");
    printf("EA texture: %s\n", pmap->ea ? pmap->ea : "(null)");
    printf("Floor color: R=%d G=%d B=%d\n",
           pmap->floor[0], pmap->floor[1], pmap->floor[2]);
    printf("Ceiling color: R=%d G=%d B=%d\n",
           pmap->ceiling[0], pmap->ceiling[1], pmap->ceiling[2]);
    printf("=================\n");
}

void    free_config_map(t_map *pmap)
{
    if (!pmap)
        return;

    free(pmap->no);
    free(pmap->so);
    free(pmap->we);
    free(pmap->ea);
    free(pmap);
}


