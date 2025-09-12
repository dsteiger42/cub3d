/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:06:43 by scarlos-          #+#    #+#             */
/*   Updated: 2025/08/29 19:15:11 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x + data->player.dir_x * MOVE_SPEED;
	ny = data->player.pos_y + data->player.dir_y * MOVE_SPEED;
	if (data->pmap->map[(int)ny][(int)nx] != '1')
	{
		data->player.pos_x = nx;
		data->player.pos_y = ny;
	}
}

void	move_backward(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x - data->player.dir_x * MOVE_SPEED;
	ny = data->player.pos_y - data->player.dir_y * MOVE_SPEED;
	if (data->pmap->map[(int)ny][(int)nx] != '1')
	{
		data->player.pos_x = nx;
		data->player.pos_y = ny;
	}
}

void	move_left(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x + data->player.dir_y * MOVE_SPEED;
	ny = data->player.pos_y - data->player.dir_x * MOVE_SPEED;
	if (data->pmap->map[(int)ny][(int)nx] != '1')
	{
		data->player.pos_x = nx;
		data->player.pos_y = ny;
	}
}

void	move_right(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x - data->player.dir_y * MOVE_SPEED;
	ny = data->player.pos_y + data->player.dir_x * MOVE_SPEED;
	if (data->pmap->map[(int)ny][(int)nx] != '1')
	{
		data->player.pos_x = nx;
		data->player.pos_y = ny;
	}
}

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(-ROT_SPEED)
		- data->player.dir_y * sin(-ROT_SPEED);
	data->player.dir_y = old_dir_x * sin(-ROT_SPEED) + data->player.dir_y
		* cos(-ROT_SPEED);
	data->player.plane_x = data->player.plane_x * cos(-ROT_SPEED)
		- data->player.plane_y * sin(-ROT_SPEED);
	data->player.plane_y = old_plane_x * sin(-ROT_SPEED) + data->player.plane_y
		* cos(-ROT_SPEED);
}

void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(ROT_SPEED)
		- data->player.dir_y * sin(ROT_SPEED);
	data->player.dir_y = old_dir_x * sin(ROT_SPEED) + data->player.dir_y
		* cos(ROT_SPEED);
	data->player.plane_x = data->player.plane_x * cos(ROT_SPEED)
		- data->player.plane_y * sin(ROT_SPEED);
	data->player.plane_y = old_plane_x * sin(ROT_SPEED) + data->player.plane_y
		* cos(ROT_SPEED);
}


int	handle_close(t_data *data)
{
	if (!data)
		exit(0);
	if (data->mlx)
		mlx_loop_end(data->mlx); // termina o loop antes de free
	return (0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == ESC && data->mlx)
		mlx_loop_end(data->mlx); // termina o loop antes de free
    else if (keycode == W)
	{
        move_forward(data);
		printf("Move forward (W)\n");
	}
	else if (keycode == S)
	{
		move_backward(data);
		printf("Move backward (S)\n");
	}
	else if (keycode == A)
	{
		move_left(data);
		printf("Move left (A)\n");
	}
	else if (keycode == D)
	{
		move_right(data);
		printf("Move right (D)\n");
	}
	else if (keycode == LEFT_ARROW)
	{
		rotate_left(data);
		printf("Rotate left (←)\n");
	}
	else if (keycode == RIGHT_ARROW)
	{
		rotate_right(data);
		printf("Rotate right (→)\n");
	}
	return (0);
}

int rotate_player(t_data *data, double angle)
{
    double old_dir_x = data->player.dir_x;
    double old_plane_x = data->player.plane_x;

    data->player.dir_x = data->player.dir_x * cos(angle)
        - data->player.dir_y * sin(angle);
    data->player.dir_y = old_dir_x * sin(angle)
        + data->player.dir_y * cos(angle);

    data->player.plane_x = data->player.plane_x * cos(angle)
        - data->player.plane_y * sin(angle);
    data->player.plane_y = old_plane_x * sin(angle)
        + data->player.plane_y * cos(angle);

    return (1);
}

/*
** Wrap cursor around window edges to keep it inside.
*/
static void wrap_mouse_position(int *x, int *y)
{
    if (*x > WIN_WIDTH - DIST_EDGE_MOUSE_WRAP)
        *x = DIST_EDGE_MOUSE_WRAP;
    else if (*x < DIST_EDGE_MOUSE_WRAP)
        *x = WIN_WIDTH - DIST_EDGE_MOUSE_WRAP;

    if (*y > WIN_HEIGHT - DIST_EDGE_MOUSE_WRAP)
        *y = DIST_EDGE_MOUSE_WRAP;
    else if (*y < DIST_EDGE_MOUSE_WRAP)
        *y = WIN_HEIGHT - DIST_EDGE_MOUSE_WRAP;
}



/*
** Mouse motion handler (event 6).
*/
int handle_mouse(int x, int y, t_data *data)
{
    static int old_x = -1;
    int         delta_x;

    if (old_x == -1) // first call → init
        old_x = x;

    wrap_mouse_position(&x, &y);

    delta_x = x - old_x;
    if (delta_x != 0)
    {
        double angle = delta_x * MOUSE_SENSITIVITY;
        rotate_player(data, angle);
    }
    old_x = x;
    return (0);
}

int	render_frame(t_data *data)
{
	// aqui você pode limpar a imagem se quiser
	raycast(data); // chama a função de raycast que desenha as paredes
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		clean_exit(data, err_msg("mlx: Could not start mlx\n", 1));
	if (init_textures(data) == -1)
		clean_exit(data, err_msg("Textures init failed\n", 1));
	data->mlx_win = mlx_new_window(data->mlx, 960, 720, "cub3D");
	if (!data->mlx_win)
		clean_exit(data, err_msg("mlx_win: Could not open mlx_window\n", 1));
	data->img = mlx_new_image(data->mlx, 960, 720);
	if (!data->img)
		clean_exit(data, err_msg("img: Could not create new image\n", 1));
	mlx_hook(data->mlx_win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->mlx_win, 17, 0, handle_close, data);
    mlx_hook(data->mlx_win, 6, 1L << 6, handle_mouse, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
}

int	init_player(t_player *player)
{
	if (!player)
		return (-1);
	player->players = 0;
	player->pos_x = -1;
	player->pos_y = -1;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	return (0);
}

int	init_map(t_map *pmap)
{
	if (!pmap)
		return (-1);
	pmap->map = NULL;
	pmap->map2 = NULL;
	pmap->line_count = 0;
	pmap->no = NULL;
	pmap->so = NULL;
	pmap->we = NULL;
	pmap->ea = NULL;
	ft_bzero(pmap->floor, sizeof(pmap->floor));
	ft_bzero(pmap->ceiling, sizeof(pmap->ceiling));
	return (0);
}

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

int	init_data_structures(t_data *data)
{
	if (!data)
		return (-1);
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->pmap = malloc(sizeof(t_map));
	if (!data->pmap)
		return (err_msg("Memory allocation failed\n", 1), -1);
	if (init_player(&data->player) == -1)
		return (free(data->pmap), err_msg("Player init failed\n", 1), -1);
	if (init_map(data->pmap) == -1)
		return (free(data->pmap), err_msg("Map init failed\n", 1), -1);
	if (init_texture(&data->textures[0]) == -1
		|| init_texture(&data->textures[1]) == -1
		|| init_texture(&data->textures[2]) == -1
		|| init_texture(&data->textures[3]) == -1)
		return (free(data->pmap), err_msg("Texture init failed\n", 1), -1);
	return (0);
}
