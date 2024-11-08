/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 02:06:43 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/08 04:08:26 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_directions_colors(t_cube *data, char *key, int idx)
{
	int			i;
	t_textures	*p;
	bool		flag;

	flag = false;
	i = 0;
	p = data->textures;
	if (p->c > 1 || p->f > 1)
		flag = true;
	if (p->ea > 1 || p->no > 1 || p->so > 1 || p->we > 1)
		flag = true;
	if (flag)
	{
		free(key);
		while (i < idx)
		{
			free(data->object[i].key);
			free(data->object[i].value);
			i++;
		}
		write_errors(data, DUPLICATE);
	}
	i = p->c + p->f + p->ea + p->no + p->so + p->we;
	return (i);
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

void	directions_colors(t_cube *data, char *key, int idx)
{
	int		i;
	char	*keys[6];
	int		*keys_lower[6];

	init_texture_maps(keys, keys_lower, data);
	i = 0;
	while (i < 6 && keys[i] != key)
	{
		if (!ft_strncmp(key, keys[i], ft_strlen(keys[i]))
			&& ft_strlen(key) == ft_strlen(keys[i]))
		{
			(*keys_lower[i])++;
			check_directions_colors(data, key, idx);
			break ;
		}
		else if (i == 5)
		{
			dprintf(2, "in direction_colors no texture found\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	initialize_game_resources(t_cube *data, int *i, int *idx)
{
	data->object = malloc(sizeof(t_map_data) * 6);
	if (!data->object)
		write_errors(data, FAILED_ALLOCATION);
	data->textures = malloc(sizeof(t_textures));
	if (!data->textures)
		write_errors(data, FAILED_ALLOCATION);
	ft_memset(data->textures, 0, sizeof(t_textures));
	*i = -1;
	*idx = 0;
}

void	set_object(t_cube *data, int *i)
{
	int		j;
	int		idx;
	char	*key;
	char	*value;

	initialize_game_resources(data, i, &idx);
	while (data->map[++(*i)])
	{
		key = NULL;
		value = NULL;
		j = 0;
		if (get_key(data, *i, &j, &key))
			break ;
		if (key)
		{
			data->idx = idx;
			directions_colors(data, key, idx);
			data->object[idx].key = ft_strdup(key);
			get_value(data, *i, &j, &value);
			data->object[idx++].value = ft_strdup(value);
		}
		free(key);
		free(value);
	}
}
