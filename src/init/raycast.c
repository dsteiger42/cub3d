#include "../includes/cub3d.h"

// RAYCAST AINDA NAO FUNCIONA, 
// FIZ ISSO AQUI NO CHAT GPT, SÓ PRA TER UMA IDEIA DO QUE PRECISAMOS
// COLOCAR NAS ESTRUTURAS...


static void put_pixel(t_data *data, int x, int y, int color)
{
    char    *dst;
    int     bpp;
    int     line;
    int     endian;

    dst = mlx_get_data_addr(data->img, &bpp, &line, &endian);
    dst += y * line + x * (bpp / 8);
    *(int *)dst = color;
}


static void draw_wall_column(t_data *data, int x, int wall_top, int wall_bottom,
                             t_texture *tex, double tex_x)
{
    int y;
    double step;
    double tex_pos;
    int tex_y;
    int color;

    step = (double)tex->height / (wall_bottom - wall_top);
    tex_pos = 0.0;
    y = wall_top;
    while (y < wall_bottom)
    {
        tex_y = (int)tex_pos & (tex->height - 1);
        color = tex->data[tex_y * tex->width + (int)tex_x];
        put_pixel(data, x, y, color);
        tex_pos += step;
        y++;
    }
}


void raycast(t_data *data)
{
    int     x;
    double  camera_x;
    double  ray_dir_x;
    double  ray_dir_y;
    int     map_x;
    int     map_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  perp_wall_dist;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;
    int     line_height;
    int     wall_top;
    int     wall_bottom;
    int     tex_index;
    double  wall_x;
    double  tex_x;

    x = 0;
    while (x < 960)
    {
        camera_x = 2.0 * x / 960 - 1.0;
        ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
        ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;

        map_x = (int)data->player.pos_x;
        map_y = (int)data->player.pos_y;

        delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
        delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

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

        hit = 0;
        while (hit == 0)
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
            if (data->pmap->map[map_y][map_x] > 0)
                hit = 1;
        }

        perp_wall_dist = (side == 0) ? (map_x - data->player.pos_x + (1 - step_x) / 2) / ray_dir_x
                                     : (map_y - data->player.pos_y + (1 - step_y) / 2) / ray_dir_y;

        line_height = (int)(720 / perp_wall_dist);
        wall_top = -line_height / 2 + 720 / 2;
        if (wall_top < 0)
            wall_top = 0;
        wall_bottom = line_height / 2 + 720 / 2;
        if (wall_bottom >= 720)
            wall_bottom = 719;

        if (side == 0 && ray_dir_x > 0)
            tex_index = 1; // sul
        else if (side == 0 && ray_dir_x < 0)
            tex_index = 0; // norte
        else if (side == 1 && ray_dir_y > 0)
            tex_index = 3; // leste
        else
            tex_index = 2; // oeste

        wall_x = (side == 0) ? data->player.pos_y + perp_wall_dist * ray_dir_y
                             : data->player.pos_x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);

        tex_x = wall_x * data->textures[tex_index].width;
        if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
            tex_x = data->textures[tex_index].width - tex_x - 1;

        draw_wall_column(data, x, wall_top, wall_bottom,
                         &data->textures[tex_index], tex_x);

        x++;
    }
}
