/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 01:05:19 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/10 06:27:56 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	file_name(char *path)
{
	int	len;

	len = 0;
	len = ft_strlen(path);
	if (len > 4 && path[len - 5] != '/')
	{
		if (!ft_strncmp(&path[len - 4], ".cub", 5))
			return ;
	}
	write_errors(NULL, FILE_NAME);
	return ;
}

void	lines_lenght(int fd, int *i)
{
	char	*line;

	*i = 0;
	line = NULL;
	while (true)
	{
		*i += +1;
		line = get_next_line(fd, 0);
		if (line == NULL)
		{
			get_next_line(fd, 1);
			free(line);
			break ;
		}
		free(line);
	}
	close(fd);
}

void	initialize_file_reading(t_cube *data, char *av, int *fd)
{
	int	i;

	file_name(av);
	*fd = open(av, O_RDONLY);
	if (*fd == FAILURE)
		write_errors(NULL, FD);
	lines_lenght(*fd, &i);
	*fd = open(av, O_RDONLY);
	data->map = ft_calloc(sizeof(char *), i + 1);
	if (!data->map)
		write_errors(NULL, FAILED_ALLOCATION);
}

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

void parse_rgb(t_cube *data)
{
	int i;
	char **splite;
	
	i = 0;
	while (data && i < 6)
	{
		if (!ft_strncmp(data->object[i].key, "F", 2))
		{
			comma_counter(data, data->object[i].value);	
			splite = split_whitespaces(data->object[i].value, ", \n\t\r\v\f");
			if (ft_strlen_2d_array(splite) == 3)
			{
				data->floor = malloc(sizeof(int) * 3);
				if (!data->floor)
				{
					free_splite(splite);
					write_errors(data, FAILED_ALLOCATION);
				}
				int xxx = 0 ;
				while (splite[xxx])
				{
					int num =  ft_atoi(splite[xxx]);
					if (  num >= 0 && num <= 255)
						data->floor[xxx] = num;
					else
					{
						free_splite(splite);
						dprintf(2, "Error: atoi(split[i] > 255 || < 0) != 3\n");
						free_all(data);
						exit(EXIT_FAILURE);
					}
					xxx++;
				}
				puts("");
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

		if (!ft_strncmp(data->object[i].key, "C", 2))
		{
			comma_counter(data, data->object[i].value);	
			splite = split_whitespaces(data->object[i].value, ", \n\t\r\v\f");
			if (ft_strlen_2d_array(splite) == 3)
			{
				data->ciel = malloc(sizeof(int) * 3);
				if (!data->ciel)
				{
					free_splite(splite);
					write_errors(data, FAILED_ALLOCATION);
				}
				int xxx = 0 ;
				while (splite[xxx])
				{
					int num =  ft_atoi(splite[xxx]);
					if (  num >= 0 && num <= 255)
						data->ciel[xxx] = num;
					else
					{
						free_splite(splite);
						dprintf(2, "Error: atoi(split[i] > 255 || < 0) != 3\n");
						free_all(data);
						exit(EXIT_FAILURE);
					}
					xxx++;
				}
				puts("");
				free_splite(splite);
			}
			else
			{
				free_splite(splite);
				dprintf(2, "Error: splite counter != 3\n");
				free_all(data);
				exit(EXIT_FAILURE);
			}	
			printf("\nCEIL %d ,%d ,%d\n", data->floor[0], data->floor[1], data->floor[2]);

		}		
		i++;
	}
}

void	controller(t_cube *data)
{
	int	i;
	int	tmp_i;

	set_object(data, &i);
	tmp_i = i;
	validate_and_set_map_dimensions(data, &i);
	parse_rgb(data);
	allocate_and_copy_map(data, tmp_i);
	to_remove_function(data);
	parse_map(data);
}

void	init(char *av, t_cube *data)
{
	int		fd;
	int		i;
	char	*line;

	initialize_file_reading(data, av, &fd);
	i = 0;
	line = NULL;
	while (true)
	{
		line = get_next_line(fd, 0);
		if (line == NULL)
		{
			get_next_line(fd, 1);
			free(line);
			break ;
		}
		data->map[i++] = ft_strdup(line);
		free(line);
	}
	controller(data);
}
