/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:23:03 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/03 16:34:48 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	ft_strchr_gnl(char *s, int c);
char	*ft_strjoin_gnl(char *remainder, char *buff);
char	*ft_get_line(char *remainder);
char	*ft_new_remainder(char *remainder);

char	*get_remainder(int fd, char *remainder)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr_gnl(remainder, '\n') && rd_bytes != 0)
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
		remainder = ft_strjoin_gnl(remainder, buff);
	}
	free(buff);
	return (remainder);
}

char	*get_next_line(int fd, int flag)
{
	char		*line;
	static char	*remainder;

	if (1 == flag)
	{
		free(remainder);
		return (NULL);
	}
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
