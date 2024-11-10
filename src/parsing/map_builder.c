/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 03:51:07 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/10 04:23:16 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*copy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		if (src[i] == 10)
			break ;
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = ' ';
		i++;
	}
	dest[i] = 0;
	return (dest);
}

void	validate_and_set_map_dimensions(t_cube *data, int *i)
{
	size_t	h;
	size_t	w;
	size_t counter;
	int   xxxxxxx = 0;
	
	counter = 0;
	h = *i;
	w = 0;
	if (check_directions_colors(data, NULL) != 6)
	{
		while (xxxxxxx <= data->idx)
		{
			free(data->object[xxxxxxx].key);
			free(data->object[xxxxxxx].value);
			xxxxxxx++;
		}
		free(data->object);
		write_errors(data, MISSED);
	}
	data->textures->map = 1;
	while (data->map[*i])
	{
		if (data->map[*i] && data->map[*i][0] == 10)
			counter++;
		else if (ft_strlen(data->map[*i]) > w)
			w = ft_strlen(data->map[*i]) - 1;
		(*i)++;
	}
	
	h = (*i - counter) - h ;
	data->height = h;
	data->width = w;
}

void	allocate_and_copy_map(t_cube *data, int tmp_i)
{
	char	**map;
	int		i;
	int		j;

	map = malloc(sizeof(char *) * (data->height + 1));
	if (map == NULL)
		write_errors(data, FAILED_ALLOCATION);
	j = 0;
	i = tmp_i;
	while (data->map[i])
	{
		if (data->map[i] && data->map[i][0] == 10)
		{
			i++;
			continue;
		}
		map[j] = malloc(sizeof(char) * (data->width + 1));
		if (map[j] == NULL)
			write_errors(data, FAILED_ALLOCATION);
		copy(map[j++], data->map[i++], data->width);
	}
	map[j] = '\0';
	free_map(data);
	data->map = map;
}
