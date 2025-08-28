/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:31:13 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/28 19:16:58 by scarlos-         ###   ########.fr       */
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

int main(int ac, char *av[])
{
	t_data data = {0};


	if (ac != 2 || init_data_structures(&data))
	{
		write(2, "\033[91mERROR\nWrong number of args\n", 33);
		free_data(&data);
		return -1;
	}
	if (valid_map_name(av[1]) == -1 || validfd(data.map, av[1]) == -1 || valid_map(av[1]) == -1)
	{
		free_data(&data);
		return -1;
	}
	free_data(&data);
	return (0);
}
