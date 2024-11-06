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

void fill_square_32(t_cube *data, int start_x, int start_y, int color)
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

void fill_player_square(t_cube *data, int start_x, int start_y, int color)
{
    int x;
    int y;

    y = 0;
    while (y < 8)
    {
        x = 0;
        while (x < 8)
        {
            my_mlx_pixel_put(data, start_x + x, start_y + y, color);
            x++;
        }
        y++;
    }
}

// int hit_wall(t_cube *data, double x, double y)
// {
// 	double tile_x = x / 32;
// 	double tile_y = y / 32;

// 	 if (tile_x < 0 || tile_x >= data->map_dim[0] || 
//         tile_y < 0 || tile_y >= data->map_dim[1])
//         return 1; 
        
//     return (data->map[tile_y][tile_x] == '1');
// }

int is_wall(t_cube *data, int x, int y)
{
    int tile_x = x / 32;
    int tile_y = y / 32;
    
    if (tile_x < 0 || tile_x >= data->map_dim[0] || 
        tile_y < 0 || tile_y >= data->map_dim[1])
        return 1; 
        
    return (data->map[tile_y][tile_x] == '1');
}

void draw_ray(t_cube *data, float ray_angle, int ray_length)
{
    double x;
    double y;
    int i = 0;
    double start_x = data->pixel_x + 4;
    double start_y = data->pixel_y + 4;

    while (i < ray_length)
    {   
        x = start_x + (i * cos(ray_angle));
        y = start_y + (i * sin(ray_angle));
        

        if (x < 0 || x >= (data->map_dim[0] * 32) || 
            y < 0 || y >= (data->map_dim[1] * 32))
            break;  

        // if (is_wall(data, x, y))
        //     break;
            
        my_mlx_pixel_put(data, x, y, 0x00FF00FF);  
        i++;
    }
}


double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}
int check_move(t_cube *data, int new_x, int new_y)
{
    return !is_wall(data, new_x, new_y) && 
           !is_wall(data, new_x + 8 - 1, new_y) && 
           !is_wall(data, new_x, new_y + 8 - 1) &&
           !is_wall(data, new_x + 8 - 1, new_y + 8 - 1);
}

void cast(t_cube *data, int ray_id, float ray_angle)
{
    // Horizontal intersection

    double xsteps_h;
	double ysteps_h;
    double xintercept_h;
	double yintercept_h;

    yintercept_h = data->pixel_y;
    xintercept_h = data->pixel_x + (data->pixel_y - yintercept_h) / tan(ray_angle);

    ysteps_h = 32;
    xsteps_h = ysteps_h / tan(ray_angle);

    if (ray_angle > M_PI) 
    { 
        ysteps_h *= -1;
        xsteps_h *= -1;
    }

    while (1)
    {
        if (is_wall(data, xintercept_h, yintercept_h))
        {
            printf("\n\nHorizontal intersection: y = %f, x = %f, ray_id = %d\n\n", yintercept_h, xintercept_h, ray_id);
            break;
        }
        xintercept_h += xsteps_h;
        yintercept_h += ysteps_h;
    }

    // Vertical intersection 

    double xsteps_v;
	double ysteps_v;
    double xintercept_v;
	double yintercept_v;

    yintercept_v = data->pixel_y;
    xintercept_v = data->pixel_x + (data->pixel_y - yintercept_v) * tan(ray_angle);

    xsteps_v = 32;
    ysteps_v = tan(ray_angle) * xsteps_v;

    if (ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2)
    { 
        xsteps_v *= -1;
        ysteps_v *= -1;
    }

    while (1)
    {
        if (is_wall(data, xintercept_v, yintercept_v))
        {
            printf("\n\nVertical Intersection: y = %f, x = %f, ray_id = %d\n\n", yintercept_v, xintercept_v, ray_id);
            break;
        }
        xintercept_v += xsteps_v;
        yintercept_v += ysteps_v;
    }

    double dx_h = xintercept_h - data->pixel_x;
    double dy_h = yintercept_h - data->pixel_y;

    double distance_h = dx_h * cos(ray_angle) + dy_h * sin(ray_angle);

    double dx_v = xintercept_v - data->pixel_x;
    double dy_v = yintercept_v - data->pixel_y;
	
    double distance_v = dx_v * cos(ray_angle) + dy_v * sin(ray_angle);

	data->closest_dis = 0;
	printf("@@@@ distance_h = %f\n",distance_h);
	printf("@@@@ distance_v = %f\n",distance_v);
    if (distance_h < distance_v)
    {
		// printf("distance_h = %d\n",distance_h);
        printf("\nHORIZONTAL x = %f, y = %f)\n", xintercept_h, yintercept_h);
		data->closest_dis = (int)distance_h;
    }
    else
    {
        printf("\nVERTICAL x = %f, y = %f)\n", xintercept_v, yintercept_v);
		data->closest_dis = (int)distance_v;
    }
}


void cast_all_rays(t_cube *data)
{
    int ray_id = 0;
    float ray_angle = data->rotation_angle - (data->fov / 2);
	data->wallhitx = 0;
	data->wallhity = 0;


    while (ray_angle < 0)
        ray_angle += 2 * M_PI;
    while (ray_angle > 2 * M_PI)
        ray_angle -= 2 * M_PI;
    
    while(ray_id < data->num_of_rays)
    {   
		// if (ray_id == data->num_of_rays / 2)
		// {
			cast(data ,ray_id, ray_angle);
        	draw_ray(data, ray_angle, data->closest_dis);
		// }
        ray_angle += data->fov / data->num_of_rays;
        if (ray_angle < 0)
            ray_angle += 2 * M_PI;
        if (ray_angle > 2 * M_PI)
            ray_angle -= 2 * M_PI;
            
        ray_id++;
    }
}

void move_player(t_cube *data, int move_direction)
{
    double new_x = data->pixel_x + move_direction * cos(data->rotation_angle) * 3;
    double new_y = data->pixel_y + move_direction * sin(data->rotation_angle) * 3;

    if (check_move(data, new_x, new_y))
    {
        mlx_clear_window(data->mlx, data->mlx_win);
        fill_square_32(data, (data->pixel_x / 32) * 32, (data->pixel_y / 32) * 32, 0x0000FF00);
        data->pixel_x = new_x;
        data->pixel_y = new_y;
        data->tile_x = data->pixel_x / 32;
        data->tile_y = data->pixel_y / 32;
        cast_all_rays(data);
        fill_player_square(data, data->pixel_x, data->pixel_y, 0x00000000);
        draw_grid_lines(data);
        mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
    }
}


int key_code(int keycode, t_cube *data)
{
    mlx_clear_window(data->mlx, data->mlx_win);
    printf("code = %d\n", keycode);
    
    if (keycode == 100)  // d key
    {
        data->rotation_angle = normalize_angle(data->rotation_angle + data->rotation_speed);
    }
    else if (keycode == 97)  // a key
    {
        data->rotation_angle = normalize_angle(data->rotation_angle - data->rotation_speed);
    }
    else if (keycode == 119)  // w key
    {
        data->turndirection = 1;
        move_player(data, 2);
    }
    else if (keycode == 115)  // s key
    {
        data->turndirection = -1;
        move_player(data, -2);
    }
    else if (keycode == 65307)  // ESC key
    {
        exit(0);
    }
    
    fill_map(data);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
    
    printf("rotation_angle = %lf\n", data->rotation_angle);
    return (1);
}


void draw_line(t_cube *data, int x, int y, int length, int is_horizontal)
{
    int i = 0;

    while (i < length)
    {
        if (is_horizontal)
            my_mlx_pixel_put(data, x + i, y, 0x000000FF); 
        else
            my_mlx_pixel_put(data, x, y + i, 0x000000FF);
        i++;
    }
}

void draw_grid_lines(t_cube *data)
{
    int	i;
	int	j;

	i = 0;
	j = 0;
    while (i < data->map_dim[1])
    {
        draw_line(data, 0, i * 32, data->map_dim[0] * 32, 1);
		i++;
    }

    while(j < data->map_dim[0])
    {
        draw_line(data, j * 32, 0, data->map_dim[1] * 32, 0);
		j++;
    }
}


void fill_map(t_cube *data)
{
    int i = 0;
    int j = 0;
    
    mlx_clear_window(data->mlx, data->mlx_win);
    data->turndirection = 0;
    data->walkdireciton = 0;
    
    while (i < data->map_dim[1])
    {
        j = 0;
        while (j < data->map_dim[0])
        {
            if (data->map[i][j] == '1')
                fill_square_32(data, j * 32, i * 32, 0x00FF0000);
            else if (data->map[i][j] == '0')
                fill_square_32(data, j * 32, i * 32, 0x0000FF00);
            j++;
        }
        i++;
    }
    fill_player_square(data, data->pixel_x, data->pixel_y, 0x00000000);
    draw_grid_lines(data);
    cast_all_rays(data);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

void player_pos(t_cube *data)
{
    int i = 0;
    int j = 0;
    data->tile_x = 0;
    data->tile_y = 0;
    data->rotation_angle = M_PI / 2;
    data->rotation_speed = 2 * (M_PI / 180);
    data->fov = 60 * (M_PI / 180);
    data->num_of_rays = data->map_dim[0] * 3;
    
    while (i < data->map_dim[1])
    {
        j = 0;
        while (j < data->map_dim[0])
        {
            if (data->map[i][j] == 'P')
            {
                data->tile_x = j;
                data->tile_y = i;
                data->pixel_x = (j * 32) + (32 - 8) / 2;
                data->pixel_y = (i * 32) + (32 - 8) / 2;
                data->map[i][j] = '0';
            }    
            j++;
        }
        i++;
    }
    printf("Tile: x = %d | y = %d\n", data->tile_x, data->tile_y);
    printf("Pixel: x = %f | y = %f\n", data->pixel_x, data->pixel_y);
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
