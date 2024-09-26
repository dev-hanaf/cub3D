#include "cub3d.h"


int	ft_close(t_cube *cube)
{
	mlx_destroy_window(cube->mlx, cube->mlx_win);
	exit(0);
	return(0);
}

int	main(int ac, char **av)
{
    if (ac == 1)
        return (0);
    (void)av;

	t_cube data;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	mlx_hook(data.mlx_win, 17, 1L<<0, ft_close, &data);
	mlx_loop(data.mlx);
}
