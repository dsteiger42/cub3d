/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:31:13 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/29 16:58:19 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

	if (valid_map_name(av[1]) || validfd(data.pmap, av[1])
			|| valid_map(&data, av[1])|| create_map(&data, av[1]))
	{
		free_data(&data);
		return -1;
	}
	free_data(&data);
	return (0);
}
