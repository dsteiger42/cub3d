/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:50:30 by dsteiger          #+#    #+#             */
/*   Updated: 2025/08/29 18:02:10 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


static void	free_textures(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < 4)
	{
		if (data->textures[i].data)
		{
			free(data->textures[i].data);
			data->textures[i].data = NULL;
		}
		i++;
	}
}

void	clean_exit(t_data *data, int exit_code)
{
	if (!data)
		exit(exit_code);
	free_textures(data);
	if (data->mlx_win && data->mlx)
		mlx_destroy_window(data->mlx, data->mlx_win);

	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		mlx_loop_end(data->mlx);
		free(data->mlx);
	}

	free_data(data);
	exit(exit_code);
}


int	err_msg(char *msg, int exit_code)
{
	ft_putstr_fd(RED "cub3D: Error", 2);
	if (msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	ft_putstr_fd("\n" RESET, 2);
	return (exit_code);
}
