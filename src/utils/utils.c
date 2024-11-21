/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 03:54:58 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/21 06:58:59 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_cube *data)
{
	int	i;

	i = 0;
	while (data->map && data->map[i])
		free(data->map[i++]);
	free(data->map);
}

int	ft_strlen_2d_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_splite(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		free(str[i++]);
	free(str);
}

bool	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

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
