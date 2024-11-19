/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:46:16 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/19 20:23:34 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	render_texture(t_cube *data, int tex_x, int tex_y, int ray_id)
{
	if (data->rays[ray_id].is_up && !data->rays[ray_id].was_hit_vertical)
	{
		data->pixel = (char *)data->addr1 + ((tex_y * data->line_length1)
				+ tex_x * (data->bits_per_pixel1 / 8));
		data->color = *(int *)data->pixel;
	}
	else if (data->rays[ray_id].is_down && !data->rays[ray_id].was_hit_vertical)
	{
		data->pixel = (char *)data->addr2 + ((tex_y * data->line_length2)
				+ tex_x * (data->bits_per_pixel2 / 8));
		data->color = *(int *)data->pixel;
	}
	else if (data->rays[ray_id].is_right && data->rays[ray_id].was_hit_vertical)
	{
		data->pixel = (char *)data->addr3 + ((tex_y * data->line_length3)
				+ tex_x * (data->bits_per_pixel3 / 8));
		data->color = *(int *)data->pixel;
	}
	else if (data->rays[ray_id].is_left && data->rays[ray_id].was_hit_vertical)
	{
		data->pixel = (char *)data->addr4 + ((tex_y * data->line_length4)
				+ tex_x * (data->bits_per_pixel4 / 8));
		data->color = *(int *)data->pixel;
	}
	return (data->color);
}

void	draw_ceiling_floor(t_cube *data, int y, int x)
{
	y = 0;
	while (y < data->wall_top)
	{
		my_mlx_pixel_put(data, x, y, data->ciel);
		y++;
	}
	y = data->wall_bottom;
	while (y < data->window_height)
	{
		my_mlx_pixel_put(data, x, y, data->floor);
		y++;
	}
}

void	render_wall(t_cube *data, int ray_id)
{
	unsigned int	color;

	color = 0;
	int y, (tex_xoffset), (tex_yoffset), (distance);
	y = data->wall_top;
	tex_xoffset = 0;
	tex_yoffset = 0;
	distance = 0;
	if (data->rays[ray_id].was_hit_vertical)
		tex_xoffset = (int)data->rays[ray_id].wallhity % TILE_SIZE;
	else
		tex_xoffset = (int)data->rays[ray_id].wallhitx % TILE_SIZE;
	while (y <= data->wall_bottom)
	{
		distance = y + (data->wallheight / 2) - (data->window_height / 2);
		tex_yoffset = distance * (TILE_SIZE / data->wallheight);
		color = render_texture(data, tex_xoffset, tex_yoffset, ray_id);
		my_mlx_pixel_put(data, ray_id, y, color);
		y++;
	}
}

void	wall_projection(t_cube *data)
{
	int		ray_id;
	int		y;
	double	disprojection;

	ray_id = 0;
	y = 0;
	while (ray_id < data->num_of_rays)
	{
		data->correct_ray = data->rays[ray_id].distance
			* cos(data->rays[ray_id].ray_angle - data->rotation_angle);
		disprojection = (data->window_width / 2) / tan(data->fov / 2);
		data->wallheight = (TILE_SIZE / data->correct_ray) * disprojection;
		data->wall_top = (data->window_height / 2) - (data->wallheight / 2);
		if (data->wall_top < 0)
			data->wall_top = 0;
		data->wall_bottom = (data->window_height / 2) + (data->wallheight / 2);
		if (data->wall_bottom >= data->window_height)
			data->wall_bottom = data->window_height;
		draw_ceiling_floor(data, y, ray_id);
		render_wall(data, ray_id);
		ray_id++;
	}
	free(data->rays);
}
