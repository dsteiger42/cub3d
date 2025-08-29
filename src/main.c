/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:31:13 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/29 15:23:51 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
void free_data(t_data *data)
{
	if (data->map)
	{
		free(data->map->map);
		free(data->map);
	}
}
int	ft_allocmap(t_data *data, char *str)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (0 * write(2, "\033[91mERROR\nInvalid file\n", 25));
	data->map->map = malloc(sizeof(char *) * (data->map->line_count + 1));
	if (!data->map->map)
		return (0 * write(2, "\033[91mERROR\nMalloc Failed\n", 26));
	i = 0;
	while (i < data->map->line_count && (line = get_next_line(fd)))
		data->map->map[i++] = line;
	data->map->map[i] = NULL;
	close(fd);
	return (1);
}




int	create_map(t_data *data,char *av)
{
		if (!ft_allocmap(data, av))
			return (-1);
		return 0;
}


int main(int ac, char *av[])
{
	t_data data = {0};


	//verificar se mantem mensagens de erros diferentes, se meter uma mensagem generica podemos fazer if(ac != 2 || init_data_structures(&data))
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

	if (valid_map_name(av[1]) == -1 || validfd(data.map, av[1]) == -1
			|| valid_map(av[1]) == -1 || create_map(&data, av[1]) == -1)
	{
		free_data(&data);
		return -1;
	}
	free_data(&data);
	return (0);
}
