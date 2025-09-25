/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:47:33 by samuel            #+#    #+#             */
/*   Updated: 2025/09/25 13:51:15 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	calculate_wall(t_ray *ray, t_player *player, t_data *data)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x)
				/ 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y)
				/ 2.0) / ray->dir_y;
	if (ray->perp_wall_dist <= 0.0)
		ray->perp_wall_dist = 1e-30;
	ray->line_height = (int)(data->screen_h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + data->screen_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->screen_h / 2;
	if (ray->draw_end >= data->screen_h)
		ray->draw_end = data->screen_h - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x = ray->wall_x - (int)ray->wall_x;
	if (ray->wall_x < 0)
		ray->wall_x += 1.0;
}

static void	init_ray(t_ray *ray, int x, t_player *player, t_data *data)
{
	ray->camera_x = 2.0 * x / data->screen_w - 1.0;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->dir_x == 0.0)
		ray->delta_dist_x = 1e30;
	else
	{
		ray->delta_dist_x = 1.0 / ray->dir_x;
		if (ray->delta_dist_x < 0)
			ray->delta_dist_x = -ray->delta_dist_x;
	}
	if (ray->dir_y == 0.0)
		ray->delta_dist_y = 1e30;
	else
	{
		ray->delta_dist_y = 1.0 / ray->dir_y;
		if (ray->delta_dist_y < 0)
			ray->delta_dist_y = -ray->delta_dist_y;
	}
}

void	raycast(t_data *data)
{
	t_img	screen;
	t_ray	ray;
	int		x;

	if (!data || !data->pmap || !data->pmap->map)
		return ;
	screen.img = data->img;
	screen.addr = (int *)mlx_get_data_addr(screen.img, &screen.pixel_bits,
			&screen.size_line, &screen.endian);
	if (!screen.addr || screen.pixel_bits != 32)
		return ;
	x = 0;
	while (x < data->screen_w)
	{
		init_ray(&ray, x, &data->player, data);
		set_dda(&ray, &data->player);
		perform_dda(&ray, data);
		calculate_wall(&ray, &data->player, data);
		draw_column(data, &screen, x, &ray);
		x++;
	}
}
