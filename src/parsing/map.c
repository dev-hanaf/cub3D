/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 06:34:27 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/17 02:09:20 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_elements(t_cube *data, char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| white_spaces(c))
		return ;
	write_errors(data, INVALID_ELEMENT);
}

void	general_check(t_cube *data, int i, int j)
{
	char	**s;
	char	c;

	s = data->map;
	c = s[i][j];
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (i == 0 || i == (int)(data->height) - 1 || j == 0
			|| j == (int)(data->width) - 1)
			write_errors(data, BAD_POSITION);
		if (white_spaces(s[i - 1][j]) || white_spaces(s[i + 1][j])
			|| white_spaces(s[i][j - 1]) || white_spaces(s[i][j + 1]))
			write_errors(data, BAD_POSITION);
	}
}

void	set_player(t_cube *data, char c, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->x = j;
		data->y = i;
		data->counter++;
	}
	if (data->counter > 1)
		write_errors(data, PLAYERS);
}

void	surrounded_check(t_cube *data)
{
	int	i;
	int	j;

	i = 0;
	data->counter = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			map_elements(data, data->map[i][j]);
			set_player(data, data->map[i][j], i, j);
			general_check(data, i, j);
			j++;
		}
		i++;
	}
	if (data->counter != 1)
		write_errors(data, PLAYERS);
}

void	parse_map(t_cube *data)
{
	surrounded_check(data);
}
