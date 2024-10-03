#include "cub3d.h"


int	ft_close(t_cube *cube)
{
	mlx_destroy_window(cube->mlx, cube->mlx_win);
	exit(0);
	return(0);
}

int	read_line(char *av)
{
	int		fd;
	int		i;
	char	*str;

	fd = open(av, O_RDONLY);
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		i++;
	}
	return (i);
}

void	map_loop(t_cube *data, char *str, int fd)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_dim[1] && str != NULL)
	{
		j = 0;
		data->map[i] = (char *)malloc(sizeof(char) * (data->map_dim[0]));
		while (j < data->map_dim[0])
		{
			data->map[i][j] = str[j];
			j++;
		}
		free(str);
		str = get_next_line(fd);
		i++;
	}
}

void	load_map(char *av, t_cube *data)
{
	int		fd;
	char	*str;

	fd = open(av, O_RDONLY);
	str = get_next_line(fd);

	data->map_dim[0] = strlen(str) - 1;
	map_loop(data, str, fd);
	close(fd);
}

void print_map(t_cube *data)
{
	int i = 0;
	int j = 0;
	while (i < data->map_dim[1])
	{
		j = 0;
		while (j < data->map_dim[0])
		{
			printf("%c", data->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	my_mlx_pixel_put(t_cube *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	fill_square(t_cube *data, int start_x, int start_y, int color)
{
	int x;
	int y;

	y = 0;
	while (y < 32)
	{
		x = 0;
		while (x < 32)
		{
			my_mlx_pixel_put(data, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

int is_wall(t_cube *data, int x, int y)
{
    int tile_x = x / 32;
    int tile_y = y / 32;
    if (tile_x < 0 || tile_x >= data->map_dim[0] || tile_y < 0 || tile_y >= data->map_dim[1])
        return 1;
    return (data->map[tile_y][tile_x] == '1');
}

int check_move(t_cube *data, int new_x, int new_y)
{
    return !is_wall(data, new_x, new_y) && !is_wall(data, new_x + 32 - 1, new_y) && !is_wall(data, new_x, new_y + 32 - 1) &&
           !is_wall(data, new_x + 32 - 1, new_y + 32 - 1);
}

void move_player(t_cube *data, int dx, int dy)
{
    int new_x = data->pixel_x + dx;
    int new_y = data->pixel_y + dy;

    if (check_move(data, new_x, new_y))
    {
        fill_square(data, data->pixel_x, data->pixel_y, 0x0000FF00);
        data->pixel_x = new_x;
        data->pixel_y = new_y;
        data->tile_x = data->pixel_x / 32;
        data->tile_y = data->pixel_y / 32;

        fill_square(data, data->pixel_x, data->pixel_y, 0x00000000);

        mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
    }
}

int key_code(int keycode, t_cube *data)
{
    printf("code = %d\n", keycode);
    if (keycode == 100) // right
        move_player(data, 1, 0);
    else if (keycode == 97) // left
        move_player(data, -1, 0);
    else if (keycode == 119) // up
        move_player(data, 0, -1);
    else if (keycode == 115) // down
        move_player(data, 0, 1);
    else if(keycode == 65307)
        exit(0);
    return (1);
}



void fill_map(t_cube *data)
{
    int i = 0;
    int j = 0;
    while (i < data->map_dim[1])
    {
        j = 0;
        while (j < data->map_dim[0])
        {
            if (data->map[i][j] == '1')
                fill_square(data, j * 32, i * 32, 0x00FF0000);
            else if (data->map[i][j] == '0' || data->map[i][j] == 'P')
                fill_square(data, j * 32, i * 32, 0x0000FF00);
            j++;
        }
        i++;
    }
    fill_square(data, data->pixel_x, data->pixel_y, 0x00000000);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

void player_pos(t_cube *data)
{
    int i = 0;
    int j = 0;
    data->tile_x = 0;
    data->tile_y = 0;
    while (i < data->map_dim[1])
    {
        j = 0;
        while (j < data->map_dim[0])
        {
            if (data->map[i][j] == 'P')
            {
                data->tile_x = j;
                data->tile_y = i;
                data->pixel_x = j * 32;
                data->pixel_y = i * 32;
                data->map[i][j] = '0';
            }	
            j++;
        }
        i++;
    }
    printf("Tile: x = %d | y = %d\n", data->tile_x, data->tile_y);
    printf("Pixel: x = %d | y = %d\n", data->pixel_x, data->pixel_y);
}

int	main(int ac, char **av)
{
	t_cube data;
    
	if (ac == 1)
        return (0);

	data.mlx = mlx_init();
	data.map_dim[1] = read_line(av[1]);
	printf("map_dim[1] = %d\n", data.map_dim[1]);
	data.map = (char **)malloc(sizeof(char *) * (data.map_dim[1] + 1));
	if (data.map == NULL)
		return 0;
	load_map(av[1], &data);
	printf("map_dim[0] = %d\n", data.map_dim[0]);
	data.mlx_win = mlx_new_window(data.mlx, data.map_dim[0] * 32, data.map_dim[1]
			* 32, "Hello world!");
	// data.mlx_win = mlx_new_window(data.mlx, 1920 , 1080, "Hello world!");
	data.img = mlx_new_image(data.mlx, data.map_dim[0] * 32, data.map_dim[1]
			* 32);
	print_map(&data);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	player_pos(&data);
	fill_map(&data);

	// my_mlx_pixel_put(&data, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_hook(data.mlx_win, 02, 1L<<0, key_code, &data);
	mlx_hook(data.mlx_win, 17, 1L<<0, ft_close, &data);
	mlx_loop(data.mlx);
}
