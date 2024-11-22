/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_atoi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:00:29 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/22 04:56:05 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vars(int *i, int *result, int *is_ok)
{
	*i = 0;
	*is_ok = 0;
	*result = 0;
}

int	advanced_atoi(char *str)
{
	int	is_ok;
	int	i;
	int	result;

	init_vars(&i, &result, &is_ok);
	while (ft_isdigit(str[i]))
	{
		is_ok = 1;
		result = result * 10 + (str[i] - '0');
		if (result > 255)
			return (-1337);
		i++;
	}
	if (!is_ok || str[i] != '\0')
		return (-1337);
	return (result);
}
