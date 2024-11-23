/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 05:52:54 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/23 23:45:04 by ahanaf           ###   ########.fr       */
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

void	controller(t_cube *data)
{
	int	i;
	int	tmp_i;

	set_object(data, &i);
	tmp_i = i;
	validate_and_set_map_dimensions(data, &i);
	parse_rgb(data);
	allocate_and_copy_map(data, tmp_i);
	parse_map(data);
}

void	init(char *av, t_cube *data)
{
	int		fd;
	int		i;
	char	*line;

	data->window_width = 1920;
	data->window_height = 1080;
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
