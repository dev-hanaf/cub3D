/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:29:36 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/11 05:47:57 by hfafouri         ###   ########.fr       */
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

typedef struct s_ray
{
	int 		*ray;
	double		ray_angle;
	double		distance;
	double		wallhitx;
	double		wallhity;
	int		flag;
}	t_ray;

typedef struct s_cast
{
	double	xsteps_h;
	double	ysteps_h;
	double	xintercept_h;
	double	yintercept_h;
	double	check_x;
	double	check_y;
	double	next_x_h;
	double	next_y_h;
	int		found_wall_h;
	double	xsteps_v;
	double	ysteps_v;
	double	xintercept_v;
	double	yintercept_v;
	double	next_x_v;
	double	next_y_v;
	int		found_wall_v;
	double	dx_h;
	double	dy_h;
	double	distance_h;
	double	dx_v;
	double	dy_v;
	double	distance_v;
}	t_cast;

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
	double		rotation_angle;
	double	fov;
	double 		closest_dis;
	int		num_of_rays;
	int		wall_strip_width;
	int		ray_up;
	int		ray_down;
	int		ray_left;
	int		ray_right;
	int		*ray;
	double sfactor;
	double ray_angle;
    int tile_x;
    int tile_y;
	t_ray *rays;
} t_cube;

void	fill_map(t_cube *data);

//== Draw

int		hit_wall(t_cube *data, double x, double y);
void	my_mlx_pixel_put(t_cube *data, int x, int y, int color);
void	draw_line(t_cube *data, int x, int y, int length, int is_horizontal);
void	draw_grid_lines(t_cube *data);
void	draw_ray(t_cube *data);

//== find hits

void	horizontal_hit(t_cast *cast, t_cube *data);
void	find_hor_hit(t_cast *cast, t_cube *data);
void	vertical_hit(t_cast *cast, t_cube *data);
void	find_ver_hit(t_cast *cast, t_cube *data);

//== raycasting

void	calcul_closest_distance(t_cast *cast, t_cube *data, t_ray *current_ray);
void	cast(t_cube *data, t_ray *current_ray);
void	init_rays(t_cube *data);
void	cast_all_rays(t_cube *data);
double	normalize_angle(double angle);

//=== moves

int	check_move(t_cube *data, double new_x, double new_y);
void	move_player(t_cube *data, double new_x, double new_y);
int	key_code(int keycode, t_cube *data);

// fill map

void	fill_square_32(t_cube *data, int start_x, int start_y, int color);
void	fill_player_square(t_cube *data, int start_x, int start_y, int color);
void	fill_map(t_cube *data);
void	player_pos(t_cube *data);

// init_var

int	ft_close(t_cube *cube);
int	is_wall(t_cube *data, int x, int y);
void    init_var(t_cube *data);

// wall projection 

void	wall_projection(t_cube *data);



#endif