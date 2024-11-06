/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahanaf <ahanaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 02:06:43 by ahanaf            #+#    #+#             */
/*   Updated: 2024/11/06 07:05:42 by ahanaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_directions_colors(t_cube *data)
{
    int i;
    t_textures *p;

    i = 0;
    p = data->textures;

    // TODO free()
    if (p->c > 1 || p->f > 1)
       write_errors(DUPLICATE);
    if (p->ea > 1 || p->no > 1 || p->so > 1 || p->we > 1)
        write_errors(DUPLICATE);
    i = p->c + p->f + p->ea + p->no + p->so + p->we;
    if (p->map == 1)
    {
        if (i == 6)
            return ;
        else
            write_errors(MISSED);
    }
}

void directions_colors(t_cube *data, t_map_data *object, char *key)
{
    // if (!ft_strncmp("SO", key, 3))
    // {
        data->textures->so++;
        check_directions_colors(data);
        object->key = ft_strdup(key);
//     }
//     else if (!ft_strncmp("NO", key, 3))
// {
//         data->textures->no++;
//         check_directions_colors(data);
//         object->key = ft_strdup(key);
// }
//     else if (!ft_strncmp("WE", key, 3))
//     {
//         data->textures->we++;
//     }
//     else if (!ft_strncmp("EA", key, 3))
//     {
//         data->textures->ea++;
//         check_directions_colors(data);
//         object->key = ft_strdup(key);
//     }
//     else if (!ft_strncmp("F", key, 2))
//     {
//         data->textures->f++;
//         check_directions_colors(data);
//         object->key = ft_strdup(key);
//     }
//     else if (!ft_strncmp("C", key, 2))
//     {
//         data->textures->c++;
//         check_directions_colors(data);
//         object->key = ft_strdup(key);
//     }
//     else
//     {
//         data->map++;
//         check_directions_colors(data);
//         object->key = ft_strdup("map");
//     }
    free(key);
}


bool controller(t_cube *data)
{
    int i;
    int j;
    int idx;
    char c[2];
    char *key;
    char *value;
    
    data->object = malloc(sizeof(t_map_data) * 6);
    data->textures = malloc(sizeof(t_textures));
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
        if (key && ( key[0] != '1' && key[0] != '0' /* TODO change [0] with j*/))
        {
            printf("%d     %s\n", idx, key);
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












    
    j = 0;
    while (j < 6)
    {
        printf("key ==> %s, value ==> %s\n", data->object[j].key, data->object[j].value);
        printf("%d ",data->textures->c);
        printf("%d ",data->textures->f);
        printf("%d ",data->textures->we);
        printf("%d ",data->textures->no);
        j++;
    }
    int x = 0;
    while (x < 6)
    {
        free(data->object[x].key);
        free(data->object[x].value);
        x++;
    }
    free(data->textures);
    free(data->object);
    
    puts("\n");
    int len_map = 0;
    j  = i;
    while (data->map[i])
    {
        len_map = 0;
        i++;
    }
    
    char **new_map = malloc(sizeof(char *) * (len_map + 1));
    int h = 0;
    while (h < len_map)
        new_map[h++] = ft_strdup(data->map[j++]);
    free_map(data);
    data->map = new_map;
    return (true);
}