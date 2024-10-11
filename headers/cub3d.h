/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:29:36 by ahanaf            #+#    #+#             */
/*   Updated: 2024/10/11 12:38:49 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <mlx.h>
//# include "/home/fafouri/Desktop/cub3D/minilibx_linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include "../includes/get_next_line/get_next_line.h"

typedef struct s_cube
{
    void	*mlx;
	void	*mlx_win;
    int     map_dim[2];
    char    **map;
    void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     x_player;
    int     y_player;
    int     pixel_x;
    int     pixel_y;
    int tile_x;
    int tile_y;
    
} t_cube;

// struct player
// {
//     float x;
//     float y;
//     int walkdirection;
//     int turndirection;
//     float walkspeed;
    
// }
// struct Ray
// {
    
// }

void	fill_map(t_cube *data);
void draw_line(t_cube *data, int x, int y, int length, int is_horizontal);
void draw_grid_lines(t_cube *data);

#endif