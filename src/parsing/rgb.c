/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 06:59:01 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/18 16:56:39 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		create_rgb(bool floor, int *array);

void	comma_counter(t_cube *data, char *rgb)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (rgb && rgb[i])
	{
		if (rgb[i] == ',')
			counter++;
		i++;
	}
	if (counter != 2)
	{
		dprintf(2, "Error: comma_counter\n");
		free_all(data);
		exit(EXIT_FAILURE);
	}
}

void	init_floor_ciel(t_cube *data, int *arrray, char **splite)
{
	int	j;
	int	num;

	j = 0;
	while (splite[j])
	{
		num = advanced_atoi(splite[j], splite, data);
		if (num >= 0 && num <= 255)
			arrray[j] = num;
		else
		{
			free_splite(splite);
			dprintf(2, "Error: atoi(split[i] > 255 || < 0) != 3\n");
			free_all(data);
			exit(EXIT_FAILURE);
		}
		j++;
	}
}

void	get_floor(t_cube *data, int i)
{
	char	**splite;
	int		floor[3];

	comma_counter(data, data->object[i].value);
	splite = split_whitespaces(data->object[i].value, ", \n\t\r\v\f");
	if (splite && ft_strlen_2d_array(splite) == 3)
	{
		init_floor_ciel(data, floor, splite);
		free_splite(splite);
		data->floor = create_rgb(true, floor);
		printf("\nFLOOR %d ,%d ,%d\n", floor[0], floor[1], floor[2]);
	}
	else
	{
		free_splite(splite);
		dprintf(2, "Error: splite counter != 3\n");
		free_all(data);
		exit(EXIT_FAILURE);
	}
}

void	get_ciel(t_cube *data, int i)
{
	char	**splite;
	int		ciel[3];

	comma_counter(data, data->object[i].value);
	splite = split_whitespaces(data->object[i].value, ", \n\t\r\v\f");
	if (splite && ft_strlen_2d_array(splite) == 3)
	{
		init_floor_ciel(data, ciel, splite);
		free_splite(splite);
		data->ciel = create_rgb(false, ciel);
		printf("\nCEIL %d ,%d ,%d\n", ciel[0], ciel[1], ciel[2]);
	}
	else
	{
		free_splite(splite);
		dprintf(2, "Error: splite counter != 3\n");
		free_all(data);
		exit(EXIT_FAILURE);
	}
}

void	parse_rgb(t_cube *data)
{
	int	i;

	i = 0;
	while (data && i < 6)
	{
		if (!ft_strncmp(data->object[i].key, "F", 2))
			get_floor(data, i);
		else if (!ft_strncmp(data->object[i].key, "C", 2))
			get_ciel(data, i);
		i++;
	}
	printf("floor ------------------------> %d\n", data->floor);
	printf("ciel  ------------------------> %d\n", data->ciel);
}
