/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:10:00 by ahanaf            #+#    #+#             */
/*   Updated: 2024/09/26 21:12:27 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "limits.h"

typedef struct s_data
{
	void			*ptr;
	struct s_data	*next;
}					t_data;

t_data				*ft_gc_lstnew(void *ptr);
void				*_malloc(size_t size);
void				_free(void);
void				*ft_calloc(size_t nmemb, size_t size);
#endif