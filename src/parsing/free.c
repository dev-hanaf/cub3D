/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:59:49 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/23 23:40:46 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_data_map(t_cube *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
	}
}

void	free_all(t_cube *data)
{
	int	i;

	i = 0;
	if (data)
	{
		free_data_map(data);
		if (data->object && data->textures->map)
		{
			while (i <= data->idx && check_directions_colors(data, NULL))
			{
				free(data->object[i].key);
				free(data->object[i++].value);
			}
			free(data->object);
		}
		if (data->textures)
			free(data->textures);
		if (data->image)
			free(data->image);
	}
}

void	write_errors(t_cube *data, t_status status)
{
	if (status == FILE_NAME)
		ft_putstr_fd("Error\nbad file name", 2);
	else if (status == FD)
		ft_putstr_fd("Error\nfd -1", 2);
	else if (status == FAILED_ALLOCATION)
		ft_putstr_fd("Error\nfailed allocation", 2);
	else if (status == BAD_ARGUMENTS)
		ft_putstr_fd("Error\nbad arguments", 2);
	else if (status == DUPLICATE)
		ft_putstr_fd("Error\ndetect a duplicate", 2);
	else if (status == MISSED)
		ft_putstr_fd("Error\nmissed arguments", 2);
	else if (status == INVALID_ELEMENT)
		ft_putstr_fd("Error\ninvalid element", 2);
	else if (status == BAD_POSITION)
		ft_putstr_fd("Error\ninvalid position", 2);
	else if (status == PLAYERS)
		ft_putstr_fd("Error\ninvalid player number", 2);
	else if (status == NO_TEXTURE_FOUND)
		ft_putstr_fd("Error\nin dirction_colors no texture found", 2);
	else if (status == ATOI)
		ft_putstr_fd("Error\n dvanced atoi", 2);
	free_all(data);
	exit(EXIT_FAILURE);
}

void	free_images(t_cube *data)
{
	if (data->image->east)
	{
		free(data->image->east);
	}
	if (data->image->west)
	{
		free(data->image->west);
	}
	if (data->image->north)
	{
		free(data->image->north);
	}
	if (data->image->south)
	{
		free(data->image->south);
	}
	ft_putstr_fd("Error\nxpm_file_to_image == NULL", 2);
	mlx_destroy_display(data->mlx);
	free_all(data);
	free(data->mlx);
	exit(EXIT_FAILURE);
}
