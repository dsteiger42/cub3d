/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:31:13 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/28 18:30:58 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int ac, char *av[])
{
	t_data data;

	init_data(&data);

    data.map = malloc(sizeof(t_map));
    if (!data.map)
    {
        write(2, "\033[91mERROR\nMemory allocation failed\n", 36);
        return -1;
    }
	init_map(data.map);

	if (ac == 2)
	{
		if (valid_map_name(av[1]) == -1 || validfd(data.map, av[1]) == -1 || valid_map(av[1]) == -1)
			return -1;
		else
			return 0;
	}
	else
	{
		write(2, "\033[91mERROR\nWrong number of args\n", 33);
		// free aqui
		return (-1);
	}
	//ft_freemap(&img); // free all and exit
	return (0);
}
