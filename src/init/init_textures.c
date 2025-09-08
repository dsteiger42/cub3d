#include "../includes/cub3d.h"

static void copy_pixels(t_texture *tex, t_img *tmp)
{
    int x;
    int y;

    y = 0;
    while (y < tex->height)
    {
        x = 0;
        while (x < tex->width)
        {
            tex->data[y * tex->width + x] = tmp->addr[y * tex->width + x];
            x++;
        }
        y++;
    }
}

static int load_texture(t_data *data, t_texture *tex, char *path)
{
    t_img tmp;

    tmp.img = mlx_xpm_file_to_image(data->mlx, path, &tex->width, &tex->height);
    if (!tmp.img)
        return (err_msg("Error to load texture\n", 1), -1);
    tmp.addr = (int *)mlx_get_data_addr(tmp.img, &tmp.pixel_bits,
            &tmp.size_line, &tmp.endian);
    tex->data = ft_calloc(tex->width * tex->height, sizeof(int));
    if (!tex->data)
    {
        mlx_destroy_image(data->mlx, tmp.img);
        return (err_msg("Error to allocate memory for texture\n", 1), -1);
    }
    copy_pixels(tex, &tmp);
    mlx_destroy_image(data->mlx, tmp.img);
    return (0);
}

int init_textures(t_data *data)
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
