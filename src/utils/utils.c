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

void	free_map_and_textures(t_map *pmap)
{
	int	i;

	if (!pmap)
		return ;
	if (pmap->map)
	{
		i = 0;
		while (i < pmap->line_count && pmap->map[i])
		{
			free(pmap->map[i]);
			i++;
		}
		free(pmap->map);
		pmap->map = NULL;
	}
	if (pmap->map2)
	{
		i = 0;
		while (i < pmap->line_count && pmap->map2[i])
		{
			free(pmap->map2[i]);
			i++;
		}
		free(pmap->map2);
		pmap->map2 = NULL;
	}
	if (pmap->no)
	{
		free(pmap->no);
		pmap->no = NULL;
	}
	if (pmap->so)
	{
		free(pmap->so);
		pmap->so = NULL;
	}
	if (pmap->we)
	{
		free(pmap->we);
		pmap->we = NULL;
	}
	if (pmap->ea)
	{
		free(pmap->ea);
		pmap->ea = NULL;
	}
	pmap->line_count = 0;
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->pmap)
	{
		free_map_and_textures(data->pmap);
		free(data->pmap);
		data->pmap = NULL;
	}
	if (data->img && data->mlx)
	{
		mlx_destroy_image(data->mlx, data->img);
		data->img = NULL;
	}
	if (data->mlx_win && data->mlx)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		data->mlx_win = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}

void	free_mlx(t_data *data)
{
	if (!data || !data->mlx)
		return ;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	data->mlx = NULL;
}
