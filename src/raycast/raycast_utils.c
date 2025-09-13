#include "../includes/cub3d.h"

int	select_texture_id(t_data *data, int side, double ray_dir_x,
		double ray_dir_y)
{
	(void)data;
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (3);
		return (2);
	}
	else
	{
		if (ray_dir_y > 0)
			return (1);
		return (0);
	}
}

/* Configura passos e sidedist inicial para DDA */
void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

/* DDA para encontrar a parede */
void	perform_dda(t_ray *ray, t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= data->pmap->line_count
			|| ray->map_x < 0
			|| ray->map_x >= (int)ft_strlen(data->pmap->map[ray->map_y]))
			break ;
		if (data->pmap->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}
