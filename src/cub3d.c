/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:18:34 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/23 23:40:18 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close(t_cube *data)
{
	mlx_destroy_image(data->mlx, data->image->south);
	mlx_destroy_image(data->mlx, data->image->north);
	mlx_destroy_image(data->mlx, data->image->west);
	mlx_destroy_image(data->mlx, data->image->east);
	mlx_destroy_image(data->mlx, data->img1);
	mlx_destroy_image(data->mlx, data->img2);
	mlx_destroy_image(data->mlx, data->img3);
	mlx_destroy_image(data->mlx, data->img4);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free_all(data);
	free(data->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

void	validate_xpm(t_cube *data)
{
	if (!data->image->east || !data->image->west || !data->image->south
		|| !data->image->north)
	{
		if (data->image->south)
			mlx_destroy_image(data->mlx, data->image->south);
		if (data->image->north)
			mlx_destroy_image(data->mlx, data->image->north);
		if (data->image->west)
			mlx_destroy_image(data->mlx, data->image->west);
		if (data->image->east)
			mlx_destroy_image(data->mlx, data->image->east);
		ft_putstr_fd("Error\nxpm_file_to_image == NULL", 2);
		mlx_destroy_display(data->mlx);
		free_all(data);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
}

void	check_textures(t_cube *data)
{
	int width, (height), (i);
	data->image = malloc(sizeof(t_images));
	if (!data->image)
		write_errors(data, FAILED_ALLOCATION);
	ft_memset(data->image, 0, sizeof(t_images));
	width = data->width;
	height = data->height;
	i = 0;
	while (i < 6)
	{
		if (data->object[i].key[0] == 'N')
			data->image->north = mlx_xpm_file_to_image(data->mlx,
					data->object[i].value, &width, &height);
		else if (data->object[i].key[0] == 'S')
			data->image->south = mlx_xpm_file_to_image(data->mlx,
					data->object[i].value, &width, &height);
		else if (data->object[i].key[0] == 'E')
			data->image->east = mlx_xpm_file_to_image(data->mlx,
					data->object[i].value, &width, &height);
		else if (data->object[i].key[0] == 'W')
			data->image->west = mlx_xpm_file_to_image(data->mlx,
					data->object[i].value, &width, &height);
		i++;
	}
	validate_xpm(data);
}

int	mlx_failed(t_cube *data, int status)
{
	if (status == 2)
	{
		mlx_destroy_image(data->mlx, data->image->south);
		mlx_destroy_image(data->mlx, data->image->north);
		mlx_destroy_image(data->mlx, data->image->west);
		mlx_destroy_image(data->mlx, data->image->east);
		mlx_destroy_image(data->mlx, data->img1);
		mlx_destroy_image(data->mlx, data->img2);
		mlx_destroy_image(data->mlx, data->img3);
		mlx_destroy_image(data->mlx, data->img4);
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free_all(data);
		free(data->mlx);
	}
	else
		free_all(data);
	return (1);
}

int	main(int ac, char **av)
{
	t_cube	data;

	ft_memset(&data, 0, sizeof(t_cube));
	if (ac != 2)
		write_errors(NULL, BAD_ARGUMENTS);
	init(av[1], &data);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		return (mlx_failed(&data, 1));
	check_textures(&data);
	data.mlx_win = mlx_new_window(data.mlx, data.window_width,
			data.window_height, "cub3d");
	if (!data.mlx_win)
		return (mlx_failed(&data, 2));
	data.img = mlx_new_image(data.mlx, data.window_width, data.window_height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	init_var(&data);
	player_pos(&data);
	fill_map(&data);
	mlx_hook(data.mlx_win, 02, 1L << 0, key_code, &data);
	mlx_hook(data.mlx_win, 17, 1L << 0, ft_close, &data);
	mlx_loop(data.mlx);
	ft_close(&data);
}
