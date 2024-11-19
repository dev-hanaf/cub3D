/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfafouri <hfafouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:24:09 by hfafouri          #+#    #+#             */
/*   Updated: 2024/11/19 21:24:30 by hfafouri         ###   ########.fr       */
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
