/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:58:27 by dsteiger          #+#    #+#             */
/*   Updated: 2025/09/04 18:25:16 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int init_and_validate(t_data *data, char *filename)
{
    if (!data || !filename)
		return 1;
	if(init_data_structures(data))
		return (1);
    if (valid_map_name(filename))
        return 1;
    if (validfd(data->pmap, filename))
        return 1;
    if (valid_map(data, filename))
        return 1;
    if (create_map(data, filename))
        return 1;

    return 0;
}

int main(int ac, char *av[])
{
	t_data data;

	if (ac != 2)
		return (err_msg("Wrong number of args\n", 1)), -1;
	if(init_and_validate(&data, av[1]))
		return (free_data(&data), -1);
	init_mlx(&data);
	free_data(&data);
	return (0);
}
