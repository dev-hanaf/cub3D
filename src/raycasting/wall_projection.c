/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:46:16 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/13 11:55:41 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int render_texture(t_cube *data, int tex_x, int tex_y)
{
	// double wall_x;
	
	// if (data->rays[ray_id].was_hit_vertical)
	// 	wall_x = data->rays[ray_id].wallhity - floor(data->rays[ray_id].wallhity);
	// else
	// 	wall_x = data->rays[ray_id].wallhitx - floor(data->rays[ray_id].wallhitx);
		
	// int tex_x = (int)(wall_x * data->tex_w);
	
	// if ((data->rays[ray_id].was_hit_vertical && data->rays[ray_id].ray_angle > M_PI_2 && 
	// 		data->rays[ray_id].ray_angle < 3 * M_PI_2) ||
	// 	(!data->rays[ray_id].was_hit_vertical && data->rays[ray_id].ray_angle > M_PI))
	// 	tex_x = data->tex_w - tex_x - 1;
		
	// double step = 1.0 * data->tex_h / data->line_length1;
	// double tex_pos = 0;
	
	// // y = 0;
	// // while(y < data->wall_top)
	// // {
	// // 	my_mlx_pixel_put(data, ray_id, y, 0x87CEEB);
	// // 	y++;
	// // }
		
	// // Draw textured wall
	// int tex_y;
	// if (tex_pos >= data->tex_h)
	// 	tex_y = (int)tex_pos % data->tex_h;
	// else 
	// 	tex_y = tex_pos;
	// tex_pos += step;
	
	char *pixel = (char *)data->addr1 + ((tex_y * data->line_length1) + tex_x * (data->bits_per_pixel1 / 8));
	int color = *(int*)pixel;
	return(color);
	// my_mlx_pixel_put(data, ray_id, y, color);
	// y = data->wall_bottom;
	// while (y < data->window_height)
	// {
	// 	my_mlx_pixel_put(data, ray_id, y, 0x808080);
	// 	y++;
	// }
    // mlx_put_image_to_window(data->mlx, data->mlx_win, data->img1, 0, 0);
    // mlx_destroy_image(data->mlx, data->img1);

}


void	wall_projection(t_cube *data)
{
	int		ray_id;
	double	ray_distance;
	int		x;
	int		y;
	double	disprojection;

	data->wall_top = 0;
	data->wall_bottom = 0;
	data->wallheight = 0;
	ray_id = 0;
	ray_distance = 0;
	data->window_width = data->width * 32;
	data->window_height = data->height * 32;
	x = 0;
	y = 0;
	while (ray_id < data->num_of_rays)
	{
		ray_distance = data->rays[ray_id].distance
			* cos(data->rays[ray_id].ray_angle - data->rotation_angle);
		disprojection = (data->window_width / 2) / tan(data->fov / 2);
		
		// printf("disprojection =  %f | ray_distance =  %f\n", disprojection, ray_distance);
		data->wallheight = (32 / ray_distance) * disprojection;
		// if (ray_distance == 0)
		// {
		// 	data->wallheight = 0;
		// }
		data->wall_top = (data->window_height / 2) - (data->wallheight / 2);
		if (data->wall_top < 0)
			data->wall_top = 0;
		// printf("data->wallheight = %f\n", data->wallheight);
		data->wall_bottom = (data->window_height / 2) + (data->wallheight / 2);
		if (data->wall_bottom >= data->window_height)
			data->wall_bottom = data->window_height - 1;
		x = ray_id;

		// Draw ceiling
		y = 0;
        while(y < data->wall_top)
		{
			
            my_mlx_pixel_put(data, x, y, 0x87CEEB);
			y++;
		}
		//== calculate tex_xoffset
		int tex_xoffset;

		if (data->rays[ray_id].was_hit_vertical)
			tex_xoffset = (int)data->rays[ray_id].wallhity % 32;
		else
			tex_xoffset = (int)data->rays[ray_id].wallhitx % 32;
		
		// render the wall
		y = data->wall_top;
		while (y <= data->wall_bottom)
		{
			int distance = 	y + (data->wallheight / 2) - (data->window_height / 2);
			int tex_yoffset = distance * (32 / data->wallheight);
			unsigned int color = render_texture(data, tex_xoffset, tex_yoffset);
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}

		// render in bot
		y = data->wall_bottom;
		// printf("%d\n",wall_bottom);
		while (y < data->window_height) 
		{
			// printf("x = %d | y = %d\n", x, y);
			my_mlx_pixel_put(data, x, y, 0x00FF00);
			y++;
		}
		ray_id++;
	}
}
