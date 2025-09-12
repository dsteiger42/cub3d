#include "../includes/cub3d.h"

#define SCREEN_W 960
#define SCREEN_H 720

static int	select_texture_id(t_data *data, int side, double ray_dir_x, double ray_dir_y)
{
	(void)data;
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (3); /* WE */
		return (2);     /* EA */
	}
	else
	{
		if (ray_dir_y > 0)
			return (1); /* SO */
		return (0);     /* NO */
	}
}


/* pega cor da textura (seguro quanto a bounds) */
static int	get_tex_color(t_texture *tex, int tx, int ty)
{
	if (!tex || !tex->data)
		return (0);
	if (tx < 0)
		tx = 0;
	if (tx >= tex->width)
		tx = tex->width - 1;
	if (ty < 0)
		ty = 0;
	if (ty >= tex->height)
		ty = tex->height - 1;
	return (tex->data[ty * tex->width + tx]);
}

/* desenha uma coluna x: preenche ceiling, parede texturizada e floor */
static void	draw_column(t_data *data, t_img *screen, int x, int draw_start,
	int draw_end, int tex_id, double wall_x)
{
	int			y;
	int			line_height;
	double		step;
	double		tex_pos;
	int			tex_y;
	int			tex_x;
	int			color;
	t_texture	*tex;

	if (!data || !screen || tex_id < 0 || tex_id > 3)
		return ;
	tex = &data->textures[tex_id];
	line_height = draw_end - draw_start + 1;
	if (line_height <= 0)
		line_height = 1;
	step = (double)tex->height / (double)line_height;
	tex_pos = 0.0;
	tex_x = (int)(wall_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;

	y = 0;
	while (y < SCREEN_H)
	{
		if (y < draw_start)
			screen->addr[y * (screen->size_line / 4) + x] =
				(data->pmap->ceiling[0] << 16) |
				(data->pmap->ceiling[1] << 8) |
				data->pmap->ceiling[2];
		else if (y <= draw_end)
		{
			tex_y = (int)tex_pos;
			color = get_tex_color(tex, tex_x, tex_y);
			screen->addr[y * (screen->size_line / 4) + x] = color;
			tex_pos += step;
		}
		else
			screen->addr[y * (screen->size_line / 4) + x] =
				(data->pmap->floor[0] << 16) |
				(data->pmap->floor[1] << 8) |
				data->pmap->floor[2];
		y++;
	}
}




/* Função principal de raycast */
void	raycast(t_data *data)
{
	t_img	screen;
	int		x;

	if (!data || !data->pmap || !data->pmap->map)
		return ;
	screen.img = data->img;
	screen.addr = (int *)mlx_get_data_addr(screen.img,
			&screen.pixel_bits, &screen.size_line, &screen.endian);
	if (!screen.addr || screen.pixel_bits != 32)
		return ;

	x = 0;
	while (x < SCREEN_W)
	{
		double	camera_x = 2.0 * (double)x / (double)SCREEN_W - 1.0;
		double	ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
		double	ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;
		int		map_x = (int)data->player.pos_x;
		int		map_y = (int)data->player.pos_y;
		double	delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
		double	delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);
		double	side_dist_x;
		double	side_dist_y;
		int		step_x;
		int		step_y;
		int		hit = 0;
		int		side = 0;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->player.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->player.pos_y) * delta_dist_y;
		}

		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map_y < 0 || map_y >= data->pmap->line_count
				|| map_x < 0 || map_x >= (int)strlen(data->pmap->map[map_y])
				|| data->pmap->map[map_y][map_x] == '1')
				hit = 1;
		}

		double	perp_wall_dist = (side == 0)
			? (map_x - data->player.pos_x + (1 - step_x) / 2.0) / ray_dir_x
			: (map_y - data->player.pos_y + (1 - step_y) / 2.0) / ray_dir_y;
		if (perp_wall_dist <= 0.0)
			perp_wall_dist = 1e-30;

		int	line_height = (int)(SCREEN_H / perp_wall_dist);
		int	draw_start = -line_height / 2 + SCREEN_H / 2;
		if (draw_start < 0)
			draw_start = 0;
		int	draw_end = line_height / 2 + SCREEN_H / 2;
		if (draw_end >= SCREEN_H)
			draw_end = SCREEN_H - 1;

		double	wall_x = (side == 0)
			? data->player.pos_y + perp_wall_dist * ray_dir_y
			: data->player.pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);

		int	tex_id = select_texture_id(data, side, ray_dir_x, ray_dir_y);
		draw_column(data, &screen, x, draw_start, draw_end, tex_id, wall_x);

		x++;
	}
}
