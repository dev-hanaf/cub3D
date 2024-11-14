/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:45:01 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/13 18:28:12 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	is_wall(t_cube *data, int x, int y)
{
	int	tile_x;
	int	tile_y;

	tile_x = x / 32;
	tile_y = y / 32;
	if (tile_x < 0 || tile_x >= data->width || tile_y < 0
		|| tile_y >= data->height)
		return (1);
	return (data->map[tile_y][tile_x] == '1');
}

void	init_var(t_cube *data)
{
	data->tile_x = 0;
	data->tile_y = 0;
	data->sfactor = 0.3;
	data->rotation_speed = 2 * (M_PI / 180);
	data->fov = 60 * (M_PI / 180);
	data->num_of_rays = data->width * 32;
	// data->img1 = mlx_xpm_file_to_image(data->mlx, "textures/ahanaf_1_32x32.xpm", &data->tex_w, &data->tex_h);
	data->img1 = mlx_xpm_file_to_image(data->mlx, "textures/wall_1.xpm", &data->tex_w, &data->tex_h);
	data->img2 = mlx_xpm_file_to_image(data->mlx, "textures/wall_2.xpm", &data->tex_w, &data->tex_h);
	data->img3 = mlx_xpm_file_to_image(data->mlx, "textures/wall_3.xpm", &data->tex_w, &data->tex_h);
	data->img4 = mlx_xpm_file_to_image(data->mlx, "textures/wall_4.xpm", &data->tex_w, &data->tex_h);
	
	data->gun = mlx_xpm_file_to_image(data->mlx, "textures/gun1.xpm", &data->tex_w1, &data->tex_h1);
	
	data->addr1 = mlx_get_data_addr(data->img1, &data->bits_per_pixel1, &data->line_length1, &data->endian1);
	data->addr2 = mlx_get_data_addr(data->img2, &data->bits_per_pixel2, &data->line_length2, &data->endian2);
	data->addr3 = mlx_get_data_addr(data->img3, &data->bits_per_pixel3, &data->line_length3, &data->endian3);
	data->addr4 = mlx_get_data_addr(data->img4, &data->bits_per_pixel4, &data->line_length4, &data->endian4);
	
}
