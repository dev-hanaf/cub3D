#include "cub3d.h"

void free_all(t_cube *data)
{
    int i;

    i = 0;
    if (data)
    {
        if (data->map)
        {
            while (data->map[i])
                free(data->map[i++]);
            free(data->map);
        }
        
        i = 0;
        if (data->object &&  data->textures->map)
        {
            while (i <= data->idx)
            {
                free(data->object[i].key);
                free(data->object[i++].value);
            }
            free(data->object);
        }
        if (data->textures)
            free(data->textures);
    }
}

void write_errors(t_cube *data, t_status status)
{
    if (status == FILE_NAME)
        dprintf(2, "Error: bad file name\n");
    else if (status == FD)
        dprintf(2, "Error: fd -1\n");
    else if (status == FAILED_ALLOCATION)
        dprintf(2, "Error: failed allocation\n");
    else if (status == BAD_ARGUMENTS)
		dprintf(2, "Error: bad arguments\n");
    else if (status == DUPLICATE)
		dprintf(2, "Error: detect a duplicate\n");
    else if (status == MISSED)
		dprintf(2, "Error: missed arguments\n");
    else if (status == INVALID_ELEMENT)
		dprintf(2, "Error: invalid element\n");
    else if (status == BAD_POSITION)
		dprintf(2, "Error: invalid position\n");
    else if (status == PLAYERS)
		dprintf(2, "Error: invalid player number\n");
    free_all(data);
    exit(EXIT_FAILURE);
}

void display_map(t_cube *data)
{
    int i;

    i = 0;
    while (data->map && data->map[i])
    {
        printf("%s\n", data->map[i++]);
    }
}

bool white_spaces(char c)
{
    if (c == 32 || (c >= 9 && c <= 13))
        return true;
    return false;
}

void	ft_strcpy(char *dst, char c)
{
	*dst++ = c;
	*dst = '\0';
}
