#include "../includes/cub3d.h"

int	init_texture(t_texture *tex)
{
	if (!tex)
		return (-1);
	tex->img = NULL;
	tex->data = NULL;
	tex->width = 0;
	tex->height = 0;
	return (0);
}

static void	copy_pixels(t_texture *tex, t_img *tmp)
{
	int	y;
	int	row_len;

	if (!tmp->addr || tmp->pixel_bits == 0)
		return ;
	row_len = tmp->size_line / (tmp->pixel_bits / 8);
	y = 0;
	while (y < tex->height)
	{
		if (tex->width <= row_len)
			memcpy(&tex->data[y * tex->width], &tmp->addr[y * row_len],
				sizeof(int) * tex->width);
		else
			memset(&tex->data[y * tex->width], 0, sizeof(int) * tex->width);
		y++;
	}
}

int	load_texture(t_data *data, t_texture *tex, char *path)
{
	t_img	tmp;

	tmp.img = mlx_xpm_file_to_image(data->mlx, path, &tex->width, &tex->height);
	if (!tmp.img)
		return (-1);
	tmp.addr = (int *)mlx_get_data_addr(tmp.img, &tmp.pixel_bits,
			&tmp.size_line, &tmp.endian);
	if (!tmp.addr)
		return (-1);
	tex->data = malloc(sizeof(int) * tex->width * tex->height);
	if (!tex->data)
		return (-1);
	copy_pixels(tex, &tmp);
	mlx_destroy_image(data->mlx, tmp.img);
	return (0);
}

int	init_textures(t_data *data)
{
	if (load_texture(data, &data->textures[0], data->pmap->no) == -1)
		return (-1);
	if (load_texture(data, &data->textures[1], data->pmap->so) == -1)
		return (-1);
	if (load_texture(data, &data->textures[2], data->pmap->we) == -1)
		return (-1);
	if (load_texture(data, &data->textures[3], data->pmap->ea) == -1)
		return (-1);
	return (0);
}

int	valid_textures(t_map *pmap)
{
	if (!pmap->no || !pmap->so || !pmap->we || !pmap->ea)
		return (err_msg("Missing texture\n", 1), -1);
	if (open_and_check(pmap->no) == -1)
		return (-1);
	if (open_and_check(pmap->so) == -1)
		return (-1);
	if (open_and_check(pmap->we) == -1)
		return (-1);
	if (open_and_check(pmap->ea) == -1)
		return (-1);
	return (0);
}
