/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 06:59:01 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/23 23:42:15 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	comma_counter(t_cube *data, char *rgb)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (rgb && rgb[i])
	{
		if (rgb[i] == ',')
		{
			counter++;
			i++;
		}
		else if (ft_isdigit(rgb[i]) || white_spaces(rgb[i]) || rgb[i] == '+')
			i++;
		else
			break ;
	}
	if (counter != 2 || rgb[i] != '\0')
	{
		ft_putstr_fd("Error\ncomma_counter", 2);
		free_all(data);
		exit(EXIT_FAILURE);
	}
}

int	verify_rgb_numbers(int *arr)
{
	int	j;

	j = 0;
	while (j < 3)
	{
		if (arr[j] == -1337)
		{
			return (1);
		}
		j++;
	}
	return (0);
}

void	free_rgb(t_cube *data, char **r, char **g, char **b)
{
	free(*r);
	free(*g);
	free(*b);
	ft_putstr_fd("Error\n-1337", 2);
	free_all(data);
	exit(EXIT_FAILURE);
}

void	fill_floor_ciel(t_cube *data, char *value, int fc)
{
	char	*red;
	char	*green;
	char	*blue;
	int		arr[3];

	red = ft_substr(value, data->rgb[0], data->rgb[1] - data->rgb[0]);
	green = ft_substr(value, data->rgb[2], data->rgb[3] - data->rgb[2]);
	blue = ft_substr(value, data->rgb[4], data->rgb[5] - data->rgb[4]);
	arr[0] = advanced_atoi(red);
	arr[1] = advanced_atoi(green);
	arr[2] = advanced_atoi(blue);
	if (verify_rgb_numbers(arr))
		free_rgb(data, &red, &green, &blue);
	if (fc == 0)
		data->floor = create_rgb(true, arr);
	else
		data->ciel = create_rgb(false, arr);
	free(red);
	free(green);
	free(blue);
}

void	parse_rgb(t_cube *data)
{
	int	i;

	i = 0;
	while (data && i < 6)
	{
		if (data->object[i].value == NULL)
		{
			free_all(data);
			ft_putstr_fd("Error\nvalue == NULL", 2);
			exit(EXIT_FAILURE);
		}
		if (!ft_strncmp(data->object[i].key, "F", 2))
			get_floor_ciel(data, data->object[i].value, 0);
		else if (!ft_strncmp(data->object[i].key, "C", 2))
			get_floor_ciel(data, data->object[i].value, 1);
		i++;
	}
}
