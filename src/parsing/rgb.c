/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 06:59:01 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/10 07:17:54 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void comma_counter(t_cube *data, char *rgb)
{
	int counter;
	int i;

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

void init_floor_ciel(t_cube *data, char **splite)
{
	int j;
	
	j= 0 ;
	while (splite[j])
	{
		//TODO change atoi
		int num =  ft_atoi(splite[j]);
		if (  num >= 0 && num <= 255)
			data->floor[j] = num;
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

void get_floor(t_cube *data, int i)
{
	char **splite;

	comma_counter(data, data->object[i].value);	
	splite = split_whitespaces(data->object[i].value, ", \n\t\r\v\f");
	if (splite &&  ft_strlen_2d_array(splite) == 3)
	{
		data->floor = malloc(sizeof(int) * 3);
		if (!data->floor)
		{
			free_splite(splite);
			write_errors(data, FAILED_ALLOCATION);
		}
		init_floor_ciel(data, splite);
		free_splite(splite);
	}
	else
	{
		free_splite(splite);
		dprintf(2, "Error: splite counter != 3\n");
		free_all(data);
		exit(EXIT_FAILURE);
	}
	printf("\nFLOOR %d ,%d ,%d\n", data->floor[0], data->floor[1], data->floor[2]);
}


void	get_ciel(t_cube *data, int i)
{
	char **splite;

	comma_counter(data, data->object[i].value);	
	splite = split_whitespaces(data->object[i].value, ", \n\t\r\v\f");
	if (splite &&  ft_strlen_2d_array(splite) == 3)
	{
		data->ciel = malloc(sizeof(int) * 3);
		if (!data->ciel)
		{
			free_splite(splite);
			write_errors(data, FAILED_ALLOCATION);
		}
		init_floor_ciel(data, splite);
		free_splite(splite);
	}
	else
	{
		free_splite(splite);
		dprintf(2, "Error: splite counter != 3\n");
		free_all(data);
		exit(EXIT_FAILURE);
	}
	printf("\nCEIL %d ,%d ,%d\n", data->ciel[0], data->ciel[1], data->ciel[2]);
}


void parse_rgb(t_cube *data)
{
	int i;

	i = 0;
	while (data && i < 6)
	{
		if (!ft_strncmp(data->object[i].key, "F", 2))
			get_floor(data, i);
		else if (!ft_strncmp(data->object[i].key, "C", 2))
			get_ciel(data, i);
		i++;
	}
}
