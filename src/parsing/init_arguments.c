#include "cub3d.h"


bool file_name(char *path)
{
    int len;

    len = 0;
    len = ft_strlen(path);
    if (len > 4 && path[len - 5] != '/')
    {
        if (!ft_strncmp(&path[len - 4], ".cub", 5))
            return (true);
    }
    write_errors(FILE_NAME);
    return (false);
}


void init_arguments(char *av, t_cube *data)
{
    int fd;
    int i;
    char *line;

    i = 0;
    file_name(av);
    fd = open(av, O_RDONLY);
    if (fd == FAILURE)
        write_errors(FD);
    data->map = ft_calloc(sizeof(char **), 20);
    if (!data->map)
        write_errors(FAILED_ALLOCATION);
    line = NULL;
    while (true)
    {
        line = get_next_line(fd, 0);
        if (line == NULL)
        {
            get_next_line(fd, 1);
            free(line);
            break;
        }
        data->map[i++] =  ft_strdup(line);
        free(line);
    }
    free(line);
    display_map(data);
    free_map(data);
    data->map = NULL;
}
