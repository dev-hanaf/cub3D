/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:29:36 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/03 16:33:20 by ahanaf           ###   ########.fr       */
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
    BAD_ARGUMENTS

}			t_status;

typedef struct s_cube
{
	void	*mlx;
	void	*mlx_win;
	char	**map;
}			t_cube;

void		init_arguments(char *av, t_cube *data);
char	    *get_next_line(int fd, int flag);

/********************** utils ******************************** */
void		write_errors(t_status status);
void        display_map(t_cube *data);
void        free_map(t_cube *data);
#endif