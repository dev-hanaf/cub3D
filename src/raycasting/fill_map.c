/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:40:23 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/12 03:58:40 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_square_32(t_cube *data, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < 32)
	{
		x = 0;
		while (x < 32)
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
	int	i;
	int	j;

	i = 0;
	j = 0;
	mlx_clear_window(data->mlx, data->mlx_win);
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (data->map[i][j] == '1')
				fill_square_32(data, j * 32, i * 32, 0x00FF0000);
			else if (data->map[i][j] == '0')
				fill_square_32(data, j * 32, i * 32, 0x0000FF00);
			j++;
		}
		i++;
	}
	cast_all_rays(data);
	fill_player_square(data, data->pixel_x, data->pixel_y, 0x00000000);
	draw_grid_lines(data);
	// wall_projection(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}
void	player_pos(t_cube *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (is_player(data->map[i][j]))
			{
				data->tile_x = j;
				data->tile_y = i;
				data->pixel_x = (j * 32) + (32 - 8) / 2;
				data->pixel_y = (i * 32) + (32 - 8) / 2;
				data->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}
