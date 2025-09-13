/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:21:07 by dsteiger          #+#    #+#             */
/*   Updated: 2025/08/29 19:08:15 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h> // open
# include <get_next_line.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>    // printf, perror
# include <stdlib.h>   // malloc, free, exit
# include <string.h>   // strerror
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // open, close, read, write

// colours for pixels
# define _BLACK 0x000000
# define _WHITE 0xFFFFFF
# define _RED 0xFF0000
# define _GREEN 0x00FF00
# define _BLUE 0x0000FF
# define _YELLOW 0xFFFF00
# define _CYAN 0x00FFFF
# define _MAGENTA 0xFF00FF
# define _GRAY 0x808080

// colours for words
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

# define W 119
# define A 97
# define S 115
# define D 100

# define UP_ARROW 65362
# define LEFT_ARROW 65361
# define DOWN_ARROW 65364
# define RIGHT_ARROW 65363
# define ESC 65307

# define MOVE_SPEED 0.02
# define ROT_SPEED 0.01
# define MOUSE_SENSITIVITY 0.003
# define DIST_EDGE_MOUSE_WRAP 10

# define PLAYER_RADIUS 0.3

typedef struct s_player
{
	double		players;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

}				t_player;

typedef struct s_map
{
	char		**map;
	char		**map2;
	int			line_count;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor[3];
	int			ceiling[3];
}				t_map;

typedef struct s_img
{
	void		*img;
	int			*addr;
	int			pixel_bits;
	int			size_line;
	int			endian;
}				t_img;

typedef struct s_texture
{
	void		*img;
	int			*data;
	int			width;
	int			height;
}				t_texture;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
	int			esc;
}				t_keys;

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int side; // 0 = x side, 1 = y side
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
}				t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*map_file;
	int			screen_w;
	int			screen_h;
	t_keys		keys;
	t_player	player;
	t_map		*pmap;
	t_texture	textures[4]; // NO, SO, WE, EA
}				t_data;

// error_exit/exit.c
void			clean_exit(t_data *data, int exit_code);
int				err_msg(char *msg, int exit_code);

// init/init_data_structures.c
int				init_player(t_player *player);
int				init_map(t_map *map);
int				init_data_structures(t_data *data);

// init/init_textures.c
int				init_texture(t_texture *tex);
int				load_texture(t_data *data, t_texture *tex, char *path);
int				init_textures(t_data *data);
int				valid_textures(t_map *pmap);

// init/init.c
int				can_move_x(t_data *data, double nx, double y);
int				can_move_y(t_data *data, double x, double ny);
int				game_loop(t_data *data);
void			init_mlx(t_data *data);

// keypress/keypress.c
int				handle_keypress(int keycode, t_data *data);
int				handle_keyrelease(int keycode, t_data *data);
int				handle_close(t_data *data);

// movement/cursor.c
int				handle_mouse(int x, int y, t_data *data);

// movement/move.c
void			move_forward(t_data *data);
void			move_backward(t_data *data);
void			move_left(t_data *data);
void			move_right(t_data *data);

// movement/rotate.c
void			rotate_left(t_data *data);
void			rotate_right(t_data *data);
int				rotate_player(t_data *data, double angle);

// parsing/map_create.c
int				dupmap(t_data *data);
int				ft_floodfill(char **map, int y, int x, int line_count);
int				create_map(t_data *data);

// parsing/map_name.c
int				valid_map_name(char *av);

// parsing/map_open.c
int				validfd(t_map *map, char *file);

// parsing/map_valid.c
int				valid_map(t_data *data);

// parsing/parse_fd.c
int				parse_file(t_data *data, char *file);

// parsing/parser_utils.c
int				valid_char(char *line);
int				open_and_check(char *path);
char			**ft_realloc(char **map, int new_size);

// raycast/raycast_utils.c
int				select_texture_id(t_data *data, int side, double ray_dir_x,
					double ray_dir_y);
void			set_dda(t_ray *ray, t_player *player);
void			perform_dda(t_ray *ray, t_data *data);

// raycast/raycast.c
void			raycast(t_data *data);

// utils/utils.c
void			ft_free_split(char **split);
void			free_map_and_textures(t_map *pmap);
void			free_data(t_data *data);
void			free_mlx(t_data *data);

// utils/utils2.c
void			print_map(char **map, int line_count);
void			print_config_map(t_map *pmap);

#endif
