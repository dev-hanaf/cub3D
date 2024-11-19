/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:39:27 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/18 10:35:45 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_move(t_cube *data, double new_x, double new_y)
{
	if (new_x < TILE_SIZE + 1 || new_x >= (data->width * TILE_SIZE) - 1
		|| new_y < TILE_SIZE + 1 || new_y >= (data->height * TILE_SIZE) - 1)
	{
		return (0);
	}
	return (!hit_wall(data, new_x, new_y) && !hit_wall(data, new_x + 8 - 1,
			new_y) && !hit_wall(data, new_x, new_y + 8 - 1) && !hit_wall(data,
			new_x + 8 - 1, new_y + 8 - 1));
}

void	move_player(t_cube *data, double new_x, double new_y)
{
	if (check_move(data, new_x, new_y))
	{
		mlx_clear_window(data->mlx, data->mlx_win);
		data->pixel_x = new_x;
		data->pixel_y = new_y;
		data->tile_x = data->pixel_x / TILE_SIZE;
		data->tile_y = data->pixel_y / TILE_SIZE;
		cast_all_rays(data);
		wall_projection(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	}
}

void	key_code_help(int keycode, t_cube *data)
{
	double new_x, (new_y);
	new_x = 0;
	new_y = 0;
	if (keycode == 119)
	{
		new_x = data->pixel_x + 1 * cos(data->rotation_angle) * 8;
		new_y = data->pixel_y + 1 * sin(data->rotation_angle) * 8;
		move_player(data, new_x, new_y);
	}
	else if (keycode == 115)
	{
		new_x = data->pixel_x - 1 * cos(data->rotation_angle) * 8;
		new_y = data->pixel_y - 1 * sin(data->rotation_angle) * 8;
		move_player(data, new_x, new_y);
	}
	else if (keycode == 65363)
	{
		data->rotation_angle = normalize_angle(data->rotation_angle
				+ data->rotation_speed);
	}
	else if (keycode == 65361)
	{
		data->rotation_angle = normalize_angle(data->rotation_angle
				- data->rotation_speed);
	}
}

int	key_code(int keycode, t_cube *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	double new_x, (new_y);
	new_x = 0;
	new_y = 0;
	if (keycode == 100)
	{
		new_x = data->pixel_x - sin(data->rotation_angle) * 8;
		new_y = data->pixel_y + cos(data->rotation_angle) * 8;
		move_player(data, new_x, new_y);
	}
	else if (keycode == 97)
	{
		new_x = data->pixel_x + sin(data->rotation_angle) * 8;
		new_y = data->pixel_y - cos(data->rotation_angle) * 8;
		move_player(data, new_x, new_y);
	}
	else if (keycode == 119 || keycode == 115 || keycode == 65363
		|| keycode == 65361)
		key_code_help(keycode, data);
	else if (keycode == 65307)
		ft_close(data);
	fill_map(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (1);
}
