/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:31:13 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/29 16:25:08 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
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

int	allocmap(t_data *data, char *str)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (0 * write(2, "\033[91mERROR\nInvalid file\n", 25));
	data->pmap->map = malloc(sizeof(char *) * (data->pmap->line_count + 1));
	if (!data->pmap->map)
		return (0 * write(2, "\033[91mERROR\nMalloc Failed\n", 26));
	i = 0;
	while (i < data->pmap->line_count && (line = get_next_line(fd)))
		data->pmap->map[i++] = line;
	data->pmap->map[i] = NULL;
	close(fd);

	return (1);
}

int	dupmap(t_data *data)
{
    int i;

    if (!data || !data->pmap || !data->pmap->map)
        return 0;
    data->pmap->map2 = malloc(sizeof(char *) * (data->pmap->line_count + 1));
    if (!data->pmap->map2)
        return 0;
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
            return -1;
        }
        i++;
    }
    data->pmap->map2[i] = NULL;
	printf("y = %d\nx = %d\n", data->start[0], data->start[1]);
	print_map(data);
    return 0;
}


int	create_map(t_data *data,char *av)
{
		if (!allocmap(data, av))
			return (-1);
		if (!dupmap(data))
			return (-1);
		return 0;
}


int main(int ac, char *av[])
{
	t_data data = {0};

	if (ac != 2)
	{
		write(2, "\033[91mERROR\nWrong number of args\n", 33);
		return -1;
	}
	if (init_data_structures(&data))
	{
		free_data(&data);
		return -1;
	}

	if (valid_map_name(av[1]) == -1 || validfd(data.pmap, av[1]) == -1
			|| valid_map(&data, av[1]) == -1 || create_map(&data, av[1]) == -1)
	{
		free_data(&data);
		return -1;
	}
	free_data(&data);
	return (0);
}
