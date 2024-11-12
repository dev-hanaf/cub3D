/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 03:54:58 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/12 03:57:55 by hfafouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_map(t_cube *data)
{
	int	i;

	i = 0;
	while (data->map && data->map[i])
	{
		printf("%s\n", data->map[i++]);
	}
}

bool	white_spaces(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

void	ft_strcpy(char *dst, char c)
{
	*dst++ = c;
	*dst = '\0';
}

void	free_map(t_cube *data)
{
	int	i;

	i = 0;
	while (data->map && data->map[i])
		free(data->map[i++]);
	free(data->map);
}

int ft_strlen_2d_array(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void free_splite(char **str)
{
	int i;

	i = 0;
	while (str && str[i])
		free(str[i++]);
	free(str);
}

bool is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}
