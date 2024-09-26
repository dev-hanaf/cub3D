/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 10:12:35 by ajordan-          #+#    #+#             */
/*   Updated: 2023/12/18 23:45:42 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

char	*get_next_line(int fd);
char	*get_remainder(int fd, char *remainder);
int		ft_strchr(char *s, int c);
char	*ft_strjoin(char *remainder, char *buff);
size_t	ft_strlen(char *s);
char	*ft_get_line(char *remainder);
char	*ft_new_remainder(char *remainder);

#endif