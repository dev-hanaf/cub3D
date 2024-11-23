/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 03:48:41 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/24 00:14:48 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	get_key(t_cube *data, int i, int *z, char **key)
{
	int		j;
	char	c[2];

	j = *z;
	while (data->map[i][j] && data->map[i][j] != 10
		&& white_spaces(data->map[i][j]))
		j++;
	*z = j;
	if (data->map[i][j] && (data->map[i][j] == '1' || data->map[i][j] == '0'))
		return (true);
	while (data->map[i][j] && data->map[i][j] != 10
		&& !white_spaces(data->map[i][j]))
	{
		ft_strcpy(c, data->map[i][j]);
		*key = ft_strjoin(*key, c);
		j++;
	}
	*z = j;
	return (false);
}

void	get_value(t_cube *data, int i, int *z, char **value)
{
	int		j;
	char	c[2];

	j = *z;
	while (data->map[i][j] && data->map[i][j] != 10
		&& white_spaces(data->map[i][j]))
		j++;
	*z = j;
	while (data->map[i][j] && data->map[i][j] != 10)
	{
		ft_strcpy(c, data->map[i][j]);
		*value = ft_strjoin(*value, c);
		j++;
	}
	*z = j;
}

void	init_texture_maps(char *keys[6], int **keys_lower, t_cube *data)
{
	keys[0] = "SO";
	keys[1] = "NO";
	keys[2] = "WE";
	keys[3] = "EA";
	keys[4] = "F";
	keys[5] = "C";
	keys_lower[0] = &data->textures->so;
	keys_lower[1] = &data->textures->no;
	keys_lower[2] = &data->textures->we;
	keys_lower[3] = &data->textures->ea;
	keys_lower[4] = &data->textures->f;
	keys_lower[5] = &data->textures->c;
}

int	create_rgb(bool floor, int *array)
{
	if (floor)
		return (0 << 24 | array[0] << 16 | array[1] << 8 | array[2]);
	return (0 << 24 | array[0] << 16 | array[1] << 8 | array[2]);
}
