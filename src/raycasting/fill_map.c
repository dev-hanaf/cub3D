/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:40:23 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/17 08:49:59 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_square_32(t_cube *data, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			my_mlx_pixel_put(data, data->sfactor * (start_x + x), data->sfactor
				* (start_y + y), color);
			x++;
		}
		y++;
	}
}

void	fill_player_square(t_cube *data, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < 8)
	{
		x = 0;
		while (x < 8)
		{
			my_mlx_pixel_put(data, data->sfactor * (start_x + x), data->sfactor
				* (start_y + y), color);
			x++;
		}
		y++;
	}
}

void	fill_map(t_cube *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	cast_all_rays(data);
	wall_projection(data);
	// render_gun(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

void	check_direction(t_cube *data)
{
	if (data->player_char == 'W')
		data->rotation_angle = M_PI;
	else if (data->player_char == 'S')
		data->rotation_angle = M_PI / 2;
	else if (data->player_char == 'E')
		data->rotation_angle = 2 * M_PI;
	else if (data->player_char == 'N')
		data->rotation_angle = -M_PI / 2;
}

void	player_pos(t_cube *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->player_char = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (is_player(data->map[i][j]))
			{
				data->player_char = data->map[i][j];
				data->tile_x = j;
				data->tile_y = i;
				data->pixel_x = (j * TILE_SIZE) + (TILE_SIZE - 8) / 2;
				data->pixel_y = (i * TILE_SIZE) + (TILE_SIZE - 8) / 2;
				data->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	check_direction(data);
}
