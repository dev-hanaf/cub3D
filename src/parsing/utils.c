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
}
