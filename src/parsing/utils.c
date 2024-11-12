/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 03:48:41 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/12 02:49:35 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(t_cube *data)
{
	int	i;

	i = 0;
	if (data)
	{
		if (data->map)
		{
			while (data->map[i])
				free(data->map[i++]);
			free(data->map);
		}
		i = 0;
		if (data->object && data->textures->map)
		{
			while (i <= data->idx)
			{
				free(data->object[i].key);
				free(data->object[i++].value);
			}
			free(data->object);
		}
		if (data->textures)
			free(data->textures);
		if (data->floor)
			free(data->floor);
		if (data->ciel)
			free(data->ciel);
		if (data->image)
			free(data->image);
	}
}

void	write_errors(t_cube *data, t_status status)
{
	if (status == FILE_NAME)
		dprintf(2, "Error: bad file name\n");
	else if (status == FD)
		dprintf(2, "Error: fd -1\n");
	else if (status == FAILED_ALLOCATION)
		dprintf(2, "Error: failed allocation\n");
	else if (status == BAD_ARGUMENTS)
		dprintf(2, "Error: bad arguments\n");
	else if (status == DUPLICATE)
		dprintf(2, "Error: detect a duplicate\n");
	else if (status == MISSED)
		dprintf(2, "Error: missed arguments\n");
	else if (status == INVALID_ELEMENT)
		dprintf(2, "Error: invalid element\n");
	else if (status == BAD_POSITION)
		dprintf(2, "Error: invalid position\n");
	else if (status == PLAYERS)
		dprintf(2, "Error: invalid player number\n");
	else if (status ==  NO_TEXTURE_FOUND)
			dprintf(2, "in direction_colors no texture found\n");
	else if (status == ATOI)
		dprintf(2, "Error : advanced atoi\n");
	free_all(data);
	exit(EXIT_FAILURE);
}

bool	get_key(t_cube *data, int i, int *z, char **key)
{
	int		j;
	char	c[2];

	j = *z;
	while (data->map[i][j] != 10 && white_spaces(data->map[i][j]))
		j++;
	*z = j;
	if (data->map[i][j] == '1' || data->map[i][j] == '0')
		return (true);
	while (data->map[i][j] != 10 && !white_spaces(data->map[i][j]))
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
	while (data->map[i][j] != 10 && white_spaces(data->map[i][j]))
		j++;
	*z = j;
	while (data->map[i][j] != 10)
	{
		ft_strcpy(c, data->map[i][j]);
		*value = ft_strjoin(*value, c);
		j++;
	}
	*z = j;
}
