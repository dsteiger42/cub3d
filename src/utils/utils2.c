/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:53:06 by samuel            #+#    #+#             */
/*   Updated: 2025/09/13 23:53:07 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map(char **map, int line_count)
{
	int	i;

	if (!map || line_count <= 0)
		return ;
	i = 0;
	printf("=== MAP ===\n");
	while (i < line_count)
	{
		printf("%s", map[i]);
		i++;
	}
}

void	print_config_map(t_map *pmap)
{
	if (!pmap)
		return ;
	printf("=== CONFIG MAP ===\n");
	if (pmap->no)
		printf("NO texture: %s\n", pmap->no);
	else
		printf("NO texture: (null)\n");
	if (pmap->so)
		printf("SO texture: %s\n", pmap->so);
	else
		printf("SO texture: (null)\n");
	if (pmap->we)
		printf("WE texture: %s\n", pmap->we);
	else
		printf("WE texture: (null)\n");
	if (pmap->ea)
		printf("EA texture: %s\n", pmap->ea);
	else
		printf("EA texture: (null)\n");
	printf("Floor color: R=%d G=%d B=%d\n", pmap->floor[0], pmap->floor[1],
		pmap->floor[2]);
	printf("Ceiling color: R=%d G=%d B=%d\n", pmap->ceiling[0],
		pmap->ceiling[1], pmap->ceiling[2]);
	printf("=================\n");
}
