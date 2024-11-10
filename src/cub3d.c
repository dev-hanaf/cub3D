/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 04:13:53 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/10 06:28:51 by ahanaf           ###   ########.fr       */
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
		printf("key->%s, value->%s\n", data->object[j].key,
			data->object[j].value);
		j++;
	}
}

int	ft_close(t_cube *cube)
{
	mlx_destroy_window(cube->mlx, cube->mlx_win);
	mlx_destroy_display(cube->mlx);
	free_all(cube);
	free(cube->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int	main(int ac, char **av)
{
	t_cube	data;

	
	ft_memset(&data, 0, sizeof(t_cube));

	data.map = NULL;
	if (ac != 2)
		write_errors(NULL, BAD_ARGUMENTS);
	init(av[1], &data);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		return (1);
	data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	if (data.mlx_win == NULL)
		return (free(data.mlx), 1);
	mlx_hook(data.mlx_win, 17, 1L << 0, ft_close, &data);
	mlx_loop(data.mlx);
	free_all(&data);
	free(data.mlx);
}
