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
#define CUB3D_H

#include <unistd.h>     // open, close, read, write
#include <fcntl.h>      // open
#include <stdio.h>      // printf, perror
#include <stdlib.h>     // malloc, free, exit
#include <string.h>     // strerror
#include <sys/time.h>   // gettimeofday
#include <math.h>
#include <libft.h>
#include <get_next_line.h>
#include <mlx.h>

// colours for pixels
#define _BLACK   0x000000
#define _WHITE   0xFFFFFF
#define _RED     0xFF0000
#define _GREEN   0x00FF00
#define _BLUE    0x0000FF
#define _YELLOW  0xFFFF00
#define _CYAN    0x00FFFF
#define _MAGENTA 0xFF00FF
#define _GRAY    0x808080

// colours for words
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

# define W 119
# define A 97
# define S 115
# define D 100

# define UP_ARROW 65362
# define LEFT_ARROW 65361
# define DOWN_ARROW 65364
# define RIGTH_ARROW 65363
# define ESC 65307

typedef struct s_player
{
	double players;
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	
}	t_player;

typedef struct s_map
{
	char	**map;
	char	**map2;
	int		line_count;
    char *no;
    char *so;
    char *we;
    char *ea;
    int floor[3];
    int ceiling[3];
}	t_map;

typedef struct s_img 
{
    void *img;
    int *addr;
    int pixel_bits;
    int size_line;
    int endian;
} t_img;


typedef struct s_texture 
{
    void *img;
    int *data;
    int width;
    int height;
} t_texture;

typedef struct s_data
{
    void        *mlx;
    void        *mlx_win;
    void        *img;
    char        *map_file;
    t_player    player;
    t_map       *pmap;
    t_texture   textures[4]; // NO, SO, WE, EA
}   t_data;


//error_exit/exit.c
void	clean_exit(t_data *data, int exit_code);
int     err_msg(char *msg, int exit_code);



//init/init.c
void	init_mlx(t_data *data);
int		init_map(t_map *map);
int		init_data_structures(t_data *data);
int     init_config_map(t_map *pmap);

//parsing/check_map.c
int     valid_map_name(char *av);
int     validfd(t_map *map, char *file);
int     valid_map(t_data *data);

//parsing/create_map.c
int	    create_map(t_data *data);
//int	    allocmap(t_data *data, char *av);
int	    dupmap(t_data *data);

//utils
void    free_data(t_data *data);
void	print_map(char **map, int line_count);
void    ft_free_split(char **split);
void    print_config_map(t_map *pmap);
void free_map_and_textures(t_map *pmap);

//parsing/parse_fd.c
int     parse_file(t_data *data, char *file);


//init/raycast.c
void raycast(t_data *data);

//init/init_textures.c
int init_textures(t_data *data);


#endif
