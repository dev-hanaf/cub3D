/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:46:16 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/12 02:03:36 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_projection(t_cube *data)
{
	int		ray_id;
	double	ray_distance;
	double	wallheight;
	int		window_width;
	int		window_height;
	int		x;
	int		y;
	double	disprojection;
	int		wall_top;
	int		wall_bottom;

	ray_id = 0;
	ray_distance = 0;
	window_width = data->map_dim[0] * 32;
	window_height = data->map_dim[1] * 32;
	x = 0;
	y = 0;
	while (ray_id < data->num_of_rays)
	{
		ray_distance = data->rays[ray_id].distance
			* cos(data->rays[ray_id].ray_angle - data->rotation_angle);
		disprojection = (window_width / 2) / tan(data->fov / 2);
		// printf("disprojection =  %f | ray_distance =  %f\n", disprojection, ray_distance);
		wallheight = (32 / ray_distance) * disprojection;
		// if (ray_distance == 0)
		// {
		// 	wallheight = 0;
		// }
		wall_top = (window_height / 2) - (wallheight / 2);
		if (wall_top < 0)
			wall_top = 0;
		// printf("wallheight = %f\n", wallheight);
		wall_bottom = (window_height / 2) + (wallheight / 2);
		if (wall_bottom >= window_height)
			wall_bottom = window_height - 1;
		x = ray_id;
		y = wall_top;
		// render the wall
		while (y <= wall_bottom)
		{
			my_mlx_pixel_put(data, x, y, 0x0000FF);
			y++;
		}
		// render somthing in top
		y = 0;
		while (y < wall_top)
		{
			my_mlx_pixel_put(data, x, y, 0xFF0000);
			y++;
		}
		// render in bot
		y = wall_bottom;
		// printf("%d\n",wall_bottom);
		while (y < window_height) 
		{
			// printf("x = %d | y = %d\n", x, y);
			my_mlx_pixel_put(data, x, y, 0x00FF00);
			y++;
		}
		ray_id++;
	}
}
