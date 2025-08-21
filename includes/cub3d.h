/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:21:07 by dsteiger          #+#    #+#             */
/*   Updated: 2025/08/21 16:21:08 by dsteiger         ###   ########.fr       */
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

#endif