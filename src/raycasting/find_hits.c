/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_hits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:33:44 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/16 11:10:50 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horizontal_hit(t_cast *cast, t_cube *data)
{
	while (!cast->found_wall_h)
	{
		if (data->ray_up)
			cast->check_y = cast->next_y_h - 1;
		else
			cast->check_y = cast->next_y_h;
		cast->check_x = cast->next_x_h;
		if (hit_wall(data, cast->check_x, cast->check_y))
		{
			cast->xintercept_h = cast->next_x_h;
			cast->yintercept_h = cast->next_y_h;
			cast->found_wall_h = 1;
			break ;
		}
		else
		{
			cast->next_x_h += cast->xsteps_h;
			cast->next_y_h += cast->ysteps_h;
		}
	}
}

void	find_hor_hit(t_cast *cast, t_cube *data)
{
	// horizontal intercept
	cast->yintercept_h = floor(data->pixel_y / TILE_SIZE) * TILE_SIZE;
	if (data->ray_down)
		cast->yintercept_h += TILE_SIZE;
	cast->xintercept_h = data->pixel_x + (cast->yintercept_h - data->pixel_y)
		/ tan(data->ray_angle);
	// calcul steps
	cast->ysteps_h = TILE_SIZE;
	if (data->ray_up)
		cast->ysteps_h *= -1;
	cast->xsteps_h = TILE_SIZE / tan(data->ray_angle);
	if ((data->ray_left && cast->xsteps_h > 0) || (data->ray_right
			&& cast->xsteps_h < 0))
		cast->xsteps_h *= -1;
	//====== check hit wall hor
	cast->check_x = 0;
	cast->check_y = 0;
	cast->next_x_h = cast->xintercept_h;
	cast->next_y_h = cast->yintercept_h;
	cast->found_wall_h = 0;
	horizontal_hit(cast, data);
}

void	vertical_hit(t_cast *cast, t_cube *data)
{
	cast->check_x = 0;
	cast->check_y = 0;
	cast->next_x_v = cast->xintercept_v;
	cast->next_y_v = cast->yintercept_v;
	cast->found_wall_v = 0;
	while (!cast->found_wall_v)
	{
		if (data->ray_left)
			cast->check_x = cast->next_x_v - 1;
		else
			cast->check_x = cast->next_x_v;
		// check_x = next_x_v;
		cast->check_y = cast->next_y_v;
		if (hit_wall(data, cast->check_x, cast->check_y))
		{
			cast->xintercept_v = cast->next_x_v;
			cast->yintercept_v = cast->next_y_v;
			cast->found_wall_v = 1;
		}
		cast->next_x_v += cast->xsteps_v;
		cast->next_y_v += cast->ysteps_v;
	}
}

void	find_ver_hit(t_cast *cast, t_cube *data)
{
	cast->xintercept_v = floor(data->pixel_x / TILE_SIZE) * TILE_SIZE;
	if (data->ray_right)
		cast->xintercept_v += TILE_SIZE;
	cast->yintercept_v = data->pixel_y + (cast->xintercept_v - data->pixel_x)
		* tan(data->ray_angle);
	//============= steps
	cast->xsteps_v = TILE_SIZE;
	if (data->ray_left)
		cast->xsteps_v *= -1;
	cast->ysteps_v = TILE_SIZE * tan(data->ray_angle);
	if ((data->ray_up && cast->ysteps_v > 0) || (data->ray_down
			&& cast->ysteps_v < 0))
	{
		cast->ysteps_v *= -1;
	}
	vertical_hit(cast, data);
}
