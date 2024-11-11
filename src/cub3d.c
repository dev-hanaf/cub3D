#include "cub3d.h"

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

void	print_map(t_cube *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

int	main(int ac, char **av)
{
	t_cube	data;

	if (ac == 1)
		return (0);
	data.mlx = mlx_init();
	data.map_dim[1] = read_line(av[1]);
	printf("map_dim[1] = %d\n", data.map_dim[1]);
	data.map = (char **)malloc(sizeof(char *) * (data.map_dim[1] + 1));
	if (data.map == NULL)
		return (0);
	load_map(av[1], &data);
	printf("map_dim[0] = %d\n", data.map_dim[0]);
	data.mlx_win = mlx_new_window(data.mlx, data.map_dim[0] * 32,
			data.map_dim[1] * 32, "Hello world!");
	// data.mlx_win = mlx_new_window(data.mlx, 1920 , 1080, "Hello world!");
	data.img = mlx_new_image(data.mlx, data.map_dim[0] * 32, data.map_dim[1]
			* 32);
	print_map(&data);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	init_var(&data);
	player_pos(&data);
	fill_map(&data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_hook(data.mlx_win, 02, 1L << 0, key_code, &data);
	mlx_hook(data.mlx_win, 17, 1L << 0, ft_close, &data);
	mlx_loop(data.mlx);
}
