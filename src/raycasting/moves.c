/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:39:27 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/12 03:44:58 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_move(t_cube *data, double new_x, double new_y)
{


    if (new_x < 32 + 1 || new_x >= (data->width * 32) - 1 || 
        new_y < 32 + 1 || new_y >= (data->height * 32) - 1)
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
		printf("new_x = %f | new_y = %f\n", new_x, new_y);
		printf("====test\n");
		mlx_clear_window(data->mlx, data->mlx_win);
		fill_square_32(data, (data->pixel_x / 32) * 32, (data->pixel_y / 32)
			* 32, 0x0000FF00);
		data->pixel_x = new_x;
		data->pixel_y = new_y;
		data->tile_x = data->pixel_x / 32;
		data->tile_y = data->pixel_y / 32;
		fill_player_square(data, data->pixel_x, data->pixel_y, 0x00000000);
		draw_grid_lines(data);
		cast_all_rays(data);
		// wall_projection(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	}
}

int	key_code(int keycode, t_cube *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	printf("code = %d\n", keycode);
	double new_x, new_y;
	new_x = 0;
	new_y = 0;
	if (keycode == 100) // d key - move right
	{
		new_x = data->pixel_x - sin(data->rotation_angle) * 2;
		new_y = data->pixel_y + cos(data->rotation_angle) * 2;
		move_player(data, new_x, new_y);
	}
	else if (keycode == 97) // a key - move left
	{
		new_x = data->pixel_x + sin(data->rotation_angle) * 2;
		new_y = data->pixel_y - cos(data->rotation_angle) * 2;
		move_player(data, new_x, new_y);
	}
	else if (keycode == 119) // w key
	{
		new_x = data->pixel_x + 1 * cos(data->rotation_angle) * 3;
		new_y = data->pixel_y + 1 * sin(data->rotation_angle) * 3;
		move_player(data, new_x, new_y);
	}
	else if (keycode == 115) // s key
	{
		new_x = data->pixel_x - 1 * cos(data->rotation_angle) * 3;
		new_y = data->pixel_y - 1 * sin(data->rotation_angle) * 3;
		move_player(data, new_x, new_y);
	}
	else if (keycode == 65363) // right arrow
	{
		data->rotation_angle = normalize_angle(data->rotation_angle
				+ data->rotation_speed);
	}
	else if (keycode == 65361) // left arrow
	{
		data->rotation_angle = normalize_angle(data->rotation_angle
				- data->rotation_speed);
	}
	else if (keycode == 65307) // ESC key
	{
		exit(0);
	}
	fill_map(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (1);
}
