#include "cub3d.h"

void write_errors(t_status status)
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

void free_map(t_cube *data)
{
    int i;

    i = 0;
    while (data->map && data->map[i])
        free(data->map[i++]);
    free(data->map);
    // free(data->object);
}

void     lines_lenght(int fd, int *i)
{
    char *line;

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
            break;
        }
        free(line);
    }
    free(line);
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
