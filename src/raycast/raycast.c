#include "../includes/cub3d.h"

void draw_square(t_data *data, int x, int y, int color)
{
    int dx, dy;

    for (dy = 0; dy < TILE_SIZE; dy++)
    {
        for (dx = 0; dx < TILE_SIZE; dx++)
        {
            my_mlx_pixel_put(data, x + dx, y + dy, color);
        }
    }
}

void draw_map(t_data *data)
{
    int row, col;
    int tile_size = get_tile_size(data);

    for (row = 0; row < data->pmap->line_count; row++)
    {
        for (col = 0; data->pmap->map[row][col]; col++)
        {
            int screen_x = col * tile_size;
            int screen_y = row * tile_size;

            if (data->pmap->map[row][col] == '1')
                draw_square(data, screen_x, screen_y, 0x808080);
            else if (data->pmap->map[row][col] == '0')
                draw_square(data, screen_x, screen_y, 0x000000);
            else if (data->pmap->map[row][col] == 'N' ||
                     data->pmap->map[row][col] == 'S' ||
                     data->pmap->map[row][col] == 'E' ||
                     data->pmap->map[row][col] == 'W')
                draw_square(data, screen_x, screen_y, 0x000000);
        }
    }
}

void draw_player(t_data *data)
{
    int tile_size = get_tile_size(data);
    int px = data->player.pos_x * tile_size;
    int py = data->player.pos_y * tile_size;

    int margin = tile_size / 4; // player smaller than tile
    for (int dy = margin; dy < tile_size - margin; dy++)
    {
        for (int dx = margin; dx < tile_size - margin; dx++)
        {
            my_mlx_pixel_put(data, px + dx, py + dy, 0xFF0000);
        }
    }
}


int get_tile_size(t_data *data)
{
    int rows = data->pmap->line_count;
    int cols = 0;
    for (int i = 0; i < rows; i++)
    {
        int len = 0;
        while (data->pmap->map[i][len])
            len++;
        if (len > cols)
            cols = len;
    }

    int tile_width = WIDTH / cols;
    int tile_height = HEIGHT / rows;

    // Use the smaller to avoid overflow
    return (tile_width < tile_height ? tile_width : tile_height);
}
