/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:59:49 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/18 17:00:14 by ahanaf           ###   ########.fr       */
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
	else if (status == NO_TEXTURE_FOUND)
		dprintf(2, "in direction_colors no texture found\n");
	else if (status == ATOI)
		dprintf(2, "Error : advanced atoi\n");
	free_all(data);
	exit(EXIT_FAILURE);
}
