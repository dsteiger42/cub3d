/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:31:03 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/29 17:40:28 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	allocmap(t_data *data, char *av)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (1 * write(2, "\033[91mERROR\nInvalid file\n", 25));
	data->pmap->map = malloc(sizeof(char *) * (data->pmap->line_count + 1));
	if (!data->pmap->map)
		return (1 * write(2, "\033[91mERROR\nMalloc Failed\n", 26));
	i = 0;
	while (i < data->pmap->line_count && (line = get_next_line(fd)))
		data->pmap->map[i++] = line;
	data->pmap->map[i] = NULL;
	close(fd);

	return (0);
}
int	dupmap(t_data *data)
{
    int i;

    if (!data || !data->pmap || !data->pmap->map)
        return 0;
    data->pmap->map2 = malloc(sizeof(char *) * (data->pmap->line_count + 1));
    if (!data->pmap->map2)
        return 1;
    i = 0;
    while (i < data->pmap->line_count)
    {
        data->pmap->map2[i] = ft_strdup(data->pmap->map[i]);
        if (!data->pmap->map2[i])
        {
            while (--i >= 0)
                free(data->pmap->map2[i]);
            free(data->pmap->map2);
            data->pmap->map2 = NULL;
            return 1;
        }
        i++;
    }
    data->pmap->map2[i] = NULL;

    return 0;
}

int ft_floodfill(char **map, int y, int x, int line_count)
{
    // verifica limites do mapa
    if (y < 0 || x < 0 || y >= line_count || !map[y] ||
		x >= (int)ft_strlen(map[y]) || map[y][x] == ' ')
	{
		printf("mapa aberto");
		return 1;
	}
    if (map[y][x] == '1')
        return 0;
    map[y][x] = '1';
    if (ft_floodfill(map, y + 1, x, line_count))
        return 1;
    if (ft_floodfill(map, y - 1, x, line_count))
        return 1;
    if (ft_floodfill(map, y, x + 1, line_count))
        return 1;
    if (ft_floodfill(map, y, x - 1, line_count))
        return 1;
    return 0;
}

int	create_map(t_data *data,char *av)
{
		if (allocmap(data, av))
			return (1);
		if (dupmap(data))
			return (1);
		if (ft_floodfill(data->pmap->map2, data->start[0], data->start[1], data->pmap->line_count))
		{
			return (1);
		}
		printf("y = %d\nx = %d\n", data->start[0], data->start[1]);
		print_map(data);
		return 0;
}
