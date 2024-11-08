/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:29:36 by ahanaf            #+#    #+#             */
/*   Updated: 2024/10/16 15:41:44 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "mlx.h"
# include <math.h>
//# include "/home/fafouri/Desktop/cub3D/minilibx_linux/mlx.h"
// # include "./minilibx_linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
//# include "/home/fafouri/Desktop/cub3D/includes/get_next_line/get_next_line.h"
# include "../includes/get_next_line/get_next_line.h"

typedef struct s_cube
{
    void	*mlx;
	void	*mlx_win;
    int     map_dim[2];
    char    **map;
	double		wallhitx;
	double		wallhity;
    void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    double     x_player;
    double     y_player;
    double     pixel_x;
    double     pixel_y;
	int		turndirection;
	int		walkdireciton;
	float		rotation_speed;
	int 	radius;
	float		rotation_angle;
	float	fov;
	double 		closest_dis;
	int		num_of_rays;
	int		wall_strip_width;
	int		ray_up;
	int		ray_down;
	int		ray_left;
	int		ray_right;
    int tile_x;
    int tile_y;
} t_cube;

typedef struct s_player
{
	int		plyr_x;
	int		plyr_y;
	double	angle;
	float	fov_rd;
	int		rot;
	int		l_r;
	int		u_d;
}	t_player;

typedef struct s_ray
{
	double	ray_ngl;
	double	distance;
	int		flag;
}	t_ray;

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