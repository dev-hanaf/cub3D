/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:30:32 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/19 21:06:32 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hit_wall(t_cube *data, double x, double y)
{
	int	tile_x;
	int	tile_y;

	tile_x = floor(x / TILE_SIZE);
	tile_y = floor(y / TILE_SIZE);
	if (tile_x < 0 || tile_x >= data->width || tile_y < 0
		|| tile_y >= data->height)
		return (1);
	return (data->map[tile_y][tile_x] == '1');
}

void	my_mlx_pixel_put(t_cube *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= data->window_width || y < 0 || y >= data->window_height)
	{
		return ;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
void	draw_line(t_cube *data, int x, int y, int length, int is_horizontal)
{
	int	i;

	i = 0;
	while (i < length)
	{
		if (is_horizontal)
			my_mlx_pixel_put(data, data->sfactor * (x + i), data->sfactor * y,
				0x000000FF);
		else
			my_mlx_pixel_put(data, data->sfactor * x, data->sfactor * (y + i),
				0x000000FF);
		i++;
	}
}

void	draw_grid_lines(t_cube *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->height)
	{
		draw_line(data, 0, i * TILE_SIZE, data->width * TILE_SIZE, 1);
		i++;
	}
	while (j < data->width)
	{
		draw_line(data, j * TILE_SIZE, 0, data->height * TILE_SIZE, 0);
		j++;
	}
}

void	draw_ray(t_cube *data)
{
	double i, (start_x), (start_y), dx, (dy), (steps), (x), (y);
	i = 0;
	start_x = data->pixel_x + 4;
	start_y = data->pixel_y + 4;
	dx = data->wallhitx - start_x;
	dy = data->wallhity - start_y;
	steps = fmax(fabs(dx), fabs(dy));
	dx /= steps;
	dy /= steps;
	x = start_x;
	y = start_y;
	while (i <= steps && !hit_wall(data, x, y))
	{
		my_mlx_pixel_put(data, round(data->sfactor * x), round(data->sfactor
				* y), 0xFFFFFFFF);
		x += dx;
		y += dy;
		i++;
	}
} */
