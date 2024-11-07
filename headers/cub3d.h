/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:29:36 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/07 06:22:53 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FAILURE -1

typedef enum e_status
{
	FD,
	FILE_NAME,
    FAILED_ALLOCATION,
    BAD_ARGUMENTS,
	DUPLICATE,
	MISSED,
	INVALID_ELEMENT,
	BAD_POSITION,
	PLAYERS

}			t_status;

typedef struct s_textures
{
	int no;
	int so;
	int we;
	int ea;
	int f;
	int c;
	int map;
}	t_textures;

typedef struct s_map_data
{
	char *key;
	char *value;
}	t_map_data;

typedef struct s_cube
{
	int 		idx;
	void		*mlx;
	void		*mlx_win;
	size_t		height;
	size_t		width;
	int			x;
	int 		y;
	int 		counter;
	char		**map;
	t_map_data 	*object;	
	t_textures	*textures;
}			t_cube;

void		init(char *av, t_cube *data);
char	    *get_next_line(int fd, int flag);
bool 		controller(t_cube *data);

/********************** utils ******************************** */
void		write_errors(t_cube *data, t_status status);
void        display_map(t_cube *data);
void 		free_all(t_cube *data);
void     	lines_lenght(int fd, int *i);
bool 		white_spaces(char c);
void	ft_strcpy(char *dst, char c);

#endif