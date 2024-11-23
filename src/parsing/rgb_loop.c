/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:50:32 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/23 23:41:25 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_rgb(t_cube *data, char *value, int *i, int start)
{
	while (value[*i] && white_spaces(value[*i]))
		(*i)++;
	if (value[*i] && value[*i] == '+')
		(*i)++;
	if (value[*i] && !ft_isdigit(value[*i]))
	{
		ft_putstr_fd("Error\nnot a digit in the first check ft_isdigit RED", 2);
		free_all(data);
		exit(EXIT_FAILURE);
	}
	data->rgb[start] = *i;
	while (value[*i] && ft_isdigit(value[*i]))
		(*i)++;
	data->rgb[start + 1] = *i;
}

void	get_comma(t_cube *data, char *value, int *i)
{
	while (value[*i] && white_spaces(value[*i]))
		(*i)++;
	if (value[*i] && value[*i] != ',')
	{
		ft_putstr_fd("Error\nnot a comma", 2);
		free_all(data);
		exit(EXIT_FAILURE);
	}
	(*i)++;
}

void	rgb_tail(t_cube *data, char *value, int *i)
{
	while (value[*i] && white_spaces(value[*i]))
		(*i)++;
	if (value[*i] != '\0')
	{
		ft_putstr_fd("Error\nthere is characters after blue", 2);
		free_all(data);
		exit(EXIT_FAILURE);
	}
}

void	get_floor_ciel(t_cube *data, char *value, int fc)
{
	int	i;

	i = 0;
	comma_counter(data, value);
	get_rgb(data, value, &i, 0);
	get_comma(data, value, &i);
	get_rgb(data, value, &i, 2);
	get_comma(data, value, &i);
	get_rgb(data, value, &i, 4);
	rgb_tail(data, value, &i);
	fill_floor_ciel(data, value, fc);
}
