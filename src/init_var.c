/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:45:01 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/12 02:32:32 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close(t_cube *cube)
{
	mlx_destroy_window(cube->mlx, cube->mlx_win);
	exit(0);
	return (0);
}

int	is_wall(t_cube *data, int x, int y)
{
	int	tile_x;
	int	tile_y;

	tile_x = x / 32;
	tile_y = y / 32;
	if (tile_x < 0 || tile_x >= data->map_dim[0] || tile_y < 0
		|| tile_y >= data->map_dim[1])
		return (1);
	return (data->map[tile_y][tile_x] == '1');
}

void	init_var(t_cube *data)
{
	data->tile_x = 0;
	data->tile_y = 0;
	data->sfactor = 1;
	data->rotation_angle = M_PI / 2;
	data->rotation_speed = 2 * (M_PI / 180);
	data->fov = 60 * (M_PI / 180);
	data->num_of_rays = data->map_dim[0] * 32;
}
