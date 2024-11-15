/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:29:36 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/12 03:58:06 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FAILURE -1


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


typedef enum e_status
{
	FD,
	FILE_NAME,
	FAILED_ALLOCATION,
	BAD_ARGUMENTS,
	DUPLICATE,
	MISSED,
	INVALID_ELEMENT,
	BAD_POSITION,
	PLAYERS,
	NO_TEXTURE_FOUND,
	ATOI
}				t_status;

typedef struct s_textures
{
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
	int			map;
}				t_textures;

typedef struct s_map_data
{
	char		*key;
	char		*value;
}				t_map_data;

typedef struct s_images
{
	void *north;
	void *east;
	void *south;
	void *west;
}	t_images;

typedef struct s_cube
{
	int			idx;
	int			*floor;
	int			*ciel;
	void		*mlx;
	void		*mlx_win;
	int		height;
	int		width;
	int			x;
	int			y;
	int			counter;
	char		**map;
	t_map_data	*object;
	t_textures	*textures;
	t_images	*image;
	//hfafouri
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
}				t_cube;


/************************** Raycasting********************************* */
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
int		check_move(t_cube *data, double new_x, double new_y);
void	move_player(t_cube *data, double new_x, double new_y);
int		key_code(int keycode, t_cube *data);
// fill map
void	fill_square_32(t_cube *data, int start_x, int start_y, int color);
void	fill_player_square(t_cube *data, int start_x, int start_y, int color);
void	fill_map(t_cube *data);
void	player_pos(t_cube *data);
// init_var
int		is_wall(t_cube *data, int x, int y);
void    init_var(t_cube *data);
// wall projection 
void	wall_projection(t_cube *data);

/************************** Parsing ********************************* */

void			init(char *av, t_cube *data);
char			*get_next_line(int fd, int flag);
void			controller(t_cube *data);
void			parse_map(t_cube *data);
char			*copy(char *dest, char *src, unsigned int n);
void			validate_and_set_map_dimensions(t_cube *data, int *i);
void			allocate_and_copy_map(t_cube *data, int tmp_i);
int				check_directions_colors(t_cube *data, char **key);
void			directions_colors(t_cube *data, char **key);
void			initialize_game_resources(t_cube *data, int *i, int *idx);
void			set_object(t_cube *data, int *i);
bool			get_key(t_cube *data, int i, int *z, char **key);
void			get_value(t_cube *data, int i, int *z, char **value);
void 			parse_rgb(t_cube *data);
int 			advanced_atoi(char *str, char **splite, t_cube *data);

/********************** utils ******************************** */
char			**split_whitespaces(char *str, char *seps);
void			write_errors(t_cube *data, t_status status);
void			display_map(t_cube *data);
void			free_all(t_cube *data);
void			lines_lenght(int fd, int *i);
bool			white_spaces(char c);
void			ft_strcpy(char *dst, char c);
void			free_map(t_cube *data);
int 			ft_strlen_2d_array(char **str);
void 			free_splite(char **str);
void			to_remove_function(t_cube *data);
bool 			is_player(char c);

#endif