/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 10:12:14 by ajordan-          #+#    #+#             */
/*   Updated: 2023/12/19 01:28:38 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_remainder(int fd, char *remainder)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(remainder, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			if (remainder)
				free(remainder);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		remainder = ft_strjoin(remainder, buff);
	}
	free(buff);
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	remainder = get_remainder(fd, remainder);
	if (!remainder)
		return (NULL);
	line = ft_get_line(remainder);
	remainder = ft_new_remainder(remainder);
	return (line);
}
