/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:32:00 by samuel            #+#    #+#             */
/*   Updated: 2025/09/15 11:00:57 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	put_pixel(t_img *screen, int x, int y, int color)
{
	screen->addr[y * (screen->size_line / 4) + x] = color;
}

static void	draw_ceiling(t_data *data, t_img *s, int x, t_ray *ray)
{
	int	y;
	int	color;

	color = (data->pmap->ceiling[0] << 16)
		| (data->pmap->ceiling[1] << 8)
		| data->pmap->ceiling[2];
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(s, x, y, color);
		y++;
	}
}

static void	draw_floor(t_data *data, t_img *s, int x, t_ray *ray)
{
	int	y;
	int	color;

	color = (data->pmap->floor[0] << 16)
		| (data->pmap->floor[1] << 8)
		| data->pmap->floor[2];
	y = ray->draw_end + 1;
	while (y < data->screen_h)
	{
		put_pixel(s, x, y, color);
		y++;
	}
}

static void	draw_wall(t_data *data, t_img *s, int x, t_ray *ray)
{
	t_texture	*tex;
	int			y;

	tex = &data->textures[select_texture_id(data, ray->side,
			ray->dir_x, ray->dir_y)];
	tex->tex_x = (int)(ray->wall_x * tex->width);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->tex_x = tex->width - tex->tex_x - 1;
	tex->step = (double)tex->height / ray->line_height;
	tex->tex_pos = (ray->draw_start - data->screen_h / 2
			+ ray->line_height / 2) * tex->step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex->tex_y = (int)tex->tex_pos & (tex->height - 1);
		put_pixel(s, x, y,
			tex->data[tex->tex_y * tex->width + tex->tex_x]);
		tex->tex_pos += tex->step;
		y++;
	}
}

void	draw_column(t_data *data, t_img *screen, int x, t_ray *ray)
{
	draw_ceiling(data, screen, x, ray);
	draw_wall(data, screen, x, ray);
	draw_floor(data, screen, x, ray);
}
