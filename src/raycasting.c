/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:36:48 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/11 05:56:58 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	calcul_closest_distance(t_cast *cast, t_cube *data, t_ray *current_ray)
{
	if (cast->distance_h < cast->distance_v)
	{
		data->closest_dis = cast->distance_h;
		data->wallhitx = cast->xintercept_h;
		data->wallhity = cast->yintercept_h;
		current_ray->distance = cast->distance_h;
		current_ray->wallhitx = cast->xintercept_h;
		current_ray->wallhity = cast->yintercept_h;
	}
	else
	{
		data->closest_dis = cast->distance_v;
		data->wallhitx = cast->xintercept_v;
		data->wallhity = cast->yintercept_v;
		current_ray->distance = cast->distance_v;
		current_ray->wallhitx = cast->xintercept_v;
		current_ray->wallhity = cast->yintercept_v;
		// printf("\nVERTICAL x = %f, y = %f\n", xintercept_v, yintercept_v);
	}
}

void	cast(t_cube *data, t_ray *current_ray)
{
	t_cast	*cast;

	cast = malloc(sizeof(t_cast));
	if (!cast)
		return ;
	memset(cast, 0, sizeof(t_cast));
	data->ray_angle = normalize_angle(data->ray_angle);
	data->ray_up = data->ray_angle > M_PI;
	data->ray_down = !data->ray_up;
	data->ray_right = data->ray_angle < M_PI_2 || data->ray_angle > 3 * M_PI_2;
	data->ray_left = !data->ray_right;
	// find first horizontal intercept
	find_hor_hit(cast, data);
	// Vertical intersection
	find_ver_hit(cast, data);
	cast->dx_h = cast->xintercept_h - data->pixel_x;
	cast->dy_h = cast->yintercept_h - data->pixel_y;
	cast->distance_h = sqrt(cast->dx_h * cast->dx_h + cast->dy_h * cast->dy_h);
	cast->dx_v = cast->xintercept_v - data->pixel_x;
	cast->dy_v = cast->yintercept_v - data->pixel_y;
	cast->distance_v = sqrt(cast->dx_v * cast->dx_v + cast->dy_v * cast->dy_v);
	calcul_closest_distance(cast, data, current_ray);
}

void	init_rays(t_cube *data)
{
	int	i;

	i = 0;
	data->rays = malloc(sizeof(t_ray) * data->num_of_rays);
	if (!data->rays)
		return ;
	while (i < data->num_of_rays)
	{
		data->rays[i].ray = NULL;
		data->rays[i].ray_angle = 0;
		data->rays[i].distance = 0;
		data->rays[i].wallhitx = 0;
		data->rays[i].wallhity = 0;
		data->rays[i].flag = 0;
		i++;
	}
}

void	cast_all_rays(t_cube *data)
{
	int		ray_id;
	double	ray_increment;

	ray_id = 0;
	ray_increment = data->fov / (data->map_dim[0] * 32);
	data->ray_angle = data->rotation_angle - (data->fov / 2);
	data->wallhitx = 0;
	data->wallhity = 0;
	data->rays = NULL;
	init_rays(data);
	while (ray_id < data->num_of_rays)
	{
		data->ray_angle = normalize_angle(data->ray_angle);
		data->rays[ray_id].ray_angle = data->ray_angle;
		cast(data, &data->rays[ray_id]);
		draw_ray(data);
		data->ray_angle += ray_increment;
		ray_id += 1;
	}
}
