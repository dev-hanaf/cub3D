/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 04:13:53 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/18 10:47:02 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	to_remove_function(t_cube *data)
{
	int	j;

	j = 0;
	while (data->map[j])
		printf("|%s|\n", data->map[j++]);
	j = 0;
	while (j < 6)
	{
		printf("key->%s, value->|%s|\n", data->object[j].key,
			data->object[j].value);
		j++;
	}
}

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
	dprintf(2, "Error : xpm_file_to_image == NULL\n");
	mlx_destroy_display(data->mlx);
	free_all(data);
	free(data->mlx);
	exit(EXIT_FAILURE);
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
		dprintf(2, "Error : xpm_file_to_image == NULL\n");
		mlx_destroy_display(data->mlx);
		free_all(data);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
}

void	check_textures(t_cube *data)
{
	int	width;
	int	height;
	int	i;

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

int	main(int ac, char **av)
{
	t_cube	data;

	ft_memset(&data, 0, sizeof(t_cube));
	if (ac != 2)
		write_errors(NULL, BAD_ARGUMENTS);
	init(av[1], &data);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
	{
		// TODO free data
		return (1);
	}
	check_textures(&data);
	data.mlx_win = mlx_new_window(data.mlx, data.window_width, data.window_height, "cub3d");
	if (!data.mlx_win)
	{
		// TODO: free mlx and data;
		return (1);
	}
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
