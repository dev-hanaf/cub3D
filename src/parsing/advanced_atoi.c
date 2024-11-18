/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_atoi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:00:29 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/18 16:53:54 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vars(int *i, int *result, int *is_ok, int *sign)
{
	*i = 0;
	*sign = 1;
	*is_ok = 0;
	*result = 0;
}

int	advanced_atoi(char *str, char **splite, t_cube *data)
{
	int	i;
	int	result;
	int	is_ok;
	int	sign;

	init_vars(&i, &result, &is_ok, &sign);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i++]))
	{
		is_ok = 1;
		result = result * 10 + (str[i] - '0');
		if (result > 255)
			break ;
	}
	if (!is_ok || str[i] != '\0')
	{
		free_splite(splite);
		write_errors(data, ATOI);
	}
	return (result * sign);
}
