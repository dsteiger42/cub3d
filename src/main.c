/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:58:27 by dsteiger          #+#    #+#             */
/*   Updated: 2025/08/29 19:10:37 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	init_mlx(&data);

	if (valid_map_name(av[1]) || validfd(data.pmap, av[1])
			|| valid_map(&data, av[1])|| create_map(&data, av[1]))
	{
		free_data(&data);
		return -1;
	}
	free_data(&data);
	return (0);
}
