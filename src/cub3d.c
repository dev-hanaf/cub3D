#include "cub3d.h"


int	ft_close(t_cube *cube)
{
	mlx_destroy_window(cube->mlx, cube->mlx_win);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	exit(EXIT_SUCCESS);
	return(0);
}

int	main(int ac, char **av)
{
	t_cube data;

	data.map = NULL;
    if (ac != 2)
		write_errors(BAD_ARGUMENTS);
	init_arguments(av[1], &data);

	data.mlx = mlx_init();
	if (data.mlx == NULL)
		return (1);
	data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	if (data.mlx_win == NULL)
		return (free(data.mlx), 1);
	mlx_hook(data.mlx_win, 17, 1L<<0, ft_close, &data);
	mlx_loop(data.mlx);
	// free_map(&data);
	free(data.mlx);
}
