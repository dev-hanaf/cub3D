/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 02:06:43 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/07 06:31:15 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_directions_colors(t_cube *data, char *key, int idx)
{
    int i;
    t_textures *p;
    bool flag;

    flag = false;
    i = 0;
    p = data->textures;
    if (p->c > 1 || p->f > 1)
        flag = true;
    if (p->ea > 1 || p->no > 1 || p->so > 1 || p->we > 1)
        flag = true;
    if (flag)
    {
        free(key);
        while (i < idx)
        {
            free(data->object[i].key);
            free(data->object[i].value);
            i++;
        }
        write_errors(data, DUPLICATE);
    }
    i = p->c + p->f + p->ea + p->no + p->so + p->we;
    return (i);
}

void directions_colors(t_cube *data, char *key, int idx)
{
    int i;
    char *keys[6] = {"SO", "NO", "WE", "EA", "F", "C"};
    int *keys_lower[6] = {&data->textures->so, &data->textures->no, &data->textures->we, &data->textures->ea, &data->textures->f, &data->textures->c};
    
    i = 0;
    while (i < 6 && keys[i] != key)
    {
        if (!ft_strncmp(key, keys[i], ft_strlen(keys[i])) && ft_strlen(key) == ft_strlen(keys[i]))
        {
            (*keys_lower[i])++;
            check_directions_colors(data, key, idx);
            break;
        }
        else if (i == 5)
        {
            dprintf(2, "in direction_colors no texture found\n");
            exit(EXIT_FAILURE);
        }
        i++;       
    }
}

char	*ft_strncpy_2(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
        if (src[i] == 10)
            break;
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = ' ';
		i++;
	}
	dest[i] = 0;
	return (dest);
}

void parse_map(t_cube *data);

bool controller(t_cube *data)
{
    int i;
    int j;
    int idx;
    char c[2];
    char *key;
    char *value;
    
    data->object = malloc(sizeof(t_map_data) * 6);
    if (!data->object)
        write_errors(data, FAILED_ALLOCATION);
    data->textures = malloc(sizeof(t_textures));
    if (!data->textures)
        write_errors(data, FAILED_ALLOCATION);
    ft_memset(data->textures, 0 ,sizeof(t_textures));





    
    i = 0;
    idx= 0;
    while (data->map[i])
    {
        key = NULL;
        value = NULL;
        j = 0;
        while (data->map[i][j] != 10 && white_spaces(data->map[i][j]))
            j++;
        if (data->map[i][j] == '1' || data->map[i][j] == '0')
            break;
        while(data->map[i][j] != 10 && !white_spaces(data->map[i][j]))
        {
            ft_strcpy(c, data->map[i][j]);
            key = ft_strjoin(key, c);
            j++;
        }


        if (key)
        {
            data->idx = idx;
            directions_colors(data, key, idx);
            data->object[idx].key = ft_strdup(key);
            while (data->map[i][j] != 10 && white_spaces(data->map[i][j]))
                j++;
            while(data->map[i][j] != 10)
            {
                ft_strcpy(c, data->map[i][j]);
                value = ft_strjoin(value, c);
                j++;
            }
            data->object[idx].value = ft_strdup(value);
            idx++;
        }
        i++;
        free(key);
        free(value);
    }




    
    if (check_directions_colors(data, NULL, 0) != 6)
        write_errors(data, MISSED);

    
    data->textures->map = 1;
    size_t h = i;
    size_t w = 0;
    int   tmp_i = i;


    while (data->map[i])
    {
        if (ft_strlen(data->map[i]) > w)
            w = ft_strlen(data->map[i]) - 1;
        i++;        
    }
    h = i - h;

    

    data->height = h;
    data->width = w;
    char    **map;
    j = 0;

    map = malloc(sizeof(char *) * (data->height + 1));
    if (map == NULL)
        write_errors(data, FAILED_ALLOCATION);
    i = tmp_i;
    while (data->map[i])
    {
        map[j] = malloc(sizeof(char) * (data->width + 1));
        if (map[j] == NULL)
            write_errors(data, FAILED_ALLOCATION);
        ft_strncpy_2(map[j++], data->map[i++], data->width);
    }
    map[j] = '\0';
    
    

    int xx = 0;
    while (data->map[xx])
        free(data->map[xx++]);
    free(data->map);
    data->map = map;
    /////////////// just to display the new map
    xx = 0;
    while (map[xx])
    {
        printf("|%s|\n", map[xx]);
        xx++;
    }

    

    /////////////// just to display the jey and value
    j = 0;
    while (j < 6)
    {
        printf("key ==> %s, value ==> %s\n", data->object[j].key, data->object[j].value);
        j++;
    }




    /******************************************MAP Parsing*********************************************/
    parse_map(data);    
    return (true);
}

void map_elements(t_cube *data, char c)
{
    if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
        || c == ' ')
        return ;
    write_errors(data, INVALID_ELEMENT);
}


void	general_check(t_cube *data, int i, int j)
{
	char	**s;
    char    c;
	s = data->map;
    c = s[i][j];
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (i == 0 || i == (int)(data->height) - 1 || j == 0
			|| j == (int)(data->width) - 1)
			write_errors(data, BAD_POSITION);
		if (s[(i) - 1][j] == ' ' || s[(i) + 1][j] == ' ' || s[i][j
			- 1] == ' ' || s[i][j + 1] == ' ')
                write_errors(data, BAD_POSITION);
	}
}

void set_player(t_cube *data, char c, int i, int j)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        data->x = j;
        data->y = i;
        data->counter++;
    }
    if (data->counter > 1)
        write_errors(data, PLAYERS);
}
void surrounded_check(t_cube *data)
{
    size_t i;
    size_t j;

    i = 0;
    data->counter = 0;
    while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {
            map_elements(data, data->map[i][j]);
            set_player(data, data->map[i][j], i, j);
            general_check(data, i , j);
            j++;
        }
        i++;
    }
    if (data->counter != 1)
        write_errors(data, PLAYERS);
}



void parse_map(t_cube *data)
{
    surrounded_check(data);
}