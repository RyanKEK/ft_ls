/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:38:20 by ohavryle          #+#    #+#             */
/*   Updated: 2019/04/08 14:38:22 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "wolf3d.h"

int rx;
int ry;

void    clear_window(t_data data, int r, int g, int b, int d)
{
    int x;
	int y;
	int index;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			index = (x + y * WIDTH) * 4;
			data.img_data[index] = b;
			data.img_data[index + 1] = g;
			data.img_data[index + 2] = r;
			data.img_data[index + 3] = d;
		}
	}
}

void	compass_facing(t_data *data)
{
	int i;
	int bpp;
	int endian;
	int size_line;

	i = -1;
	data->tx_ptrs = malloc(sizeof(void*) * 4);
	data->tx_datas = malloc(sizeof(char*) * 4);
	data->tx_ptrs[0] = mlx_xpm_file_to_image(data->mlx_ptr, "txs/dark_wolf_wall", &data->w[0], &data->h[0]);
	data->tx_datas[0] = mlx_get_data_addr(data->tx_ptrs[0], &bpp, &size_line, &endian);
	data->tx_ptrs[1] = mlx_xpm_file_to_image(data->mlx_ptr, "txs/wolf_wall", &data->w[1], &data->h[1]);
	data->tx_datas[1] = mlx_get_data_addr(data->tx_ptrs[1], &bpp, &size_line, &endian);
	data->tx_ptrs[2] = mlx_xpm_file_to_image(data->mlx_ptr, "txs/wolf_logo_dark", &data->w[2], &data->h[2]);
	data->tx_datas[2] = mlx_get_data_addr(data->tx_ptrs[2], &bpp, &size_line, &endian);
	data->tx_ptrs[3] = mlx_xpm_file_to_image(data->mlx_ptr, "txs/wolf_logo", &data->w[3], &data->h[3]);
	data->tx_datas[3] = mlx_get_data_addr(data->tx_ptrs[3], &bpp, &size_line, &endian);
}

void	crt_textures(char **av, int ac, t_data *data)
{
    int i;
    int bpp;
    int endian;
    int size_line;
	int j;


    i = 1;
    j = 0;
	while (++i < ac)
		if (mlx_xpm_file_to_image(data->mlx_ptr, av[i], &data->w[j], &data->h[j]))
			j++;
	printf("JJJ:  %d\n", j);
	data->textures = j;
	if (j > 0)
	{
		data->tx_ptrs = malloc(sizeof(void *) * j);
		data->tx_datas = malloc(sizeof(char *) * j);
		i = 1;
		j = -1;
		while (++i < ac)
		{
			j++;
			if (!(data->tx_ptrs[j] = mlx_xpm_file_to_image(data->mlx_ptr, av[i], &data->w[j], &data->h[j]))) {
				ft_putstr("There is no such file: ");
				ft_putstr(av[i]);
				ft_putchar('\n');
				j--;
				continue;
			}
			data->tx_datas[j] = mlx_get_data_addr(data->tx_ptrs[j], &bpp, &size_line, &endian);
		}
	}
	else
		compass_facing(data);
}

void	crt_floor_and_ceiling_tex(t_data *data)
{
	int bpp;
	int endian;
	int size_line;

	data->floor_tex = malloc(sizeof(void *));
	data->floor_data = malloc(sizeof(char *));
	data->ceiling_tex = malloc(sizeof(void *));
	data->ceiling_data = malloc(sizeof(char *));
	if (!(data->floor_tex = mlx_xpm_file_to_image(data->mlx_ptr, "txs/floor.xpm", &data->floor_w, &data->floor_h)))
	{
		ft_putstr("There is no floor texture =(.\n");
		exit(42);
	}
	if (!(data->ceiling_tex = mlx_xpm_file_to_image(data->mlx_ptr, "txs/ceiling2.xpm", &data->ceiling_w, &data->ceiling_h)))
	{
		ft_putstr("There is no ceiling texture =(.\n");
		exit(42);
	}
	data->floor_data = mlx_get_data_addr(data->floor_tex, &bpp, &size_line, &endian);
	data->ceiling_data = mlx_get_data_addr(data->ceiling_tex, &bpp, &size_line, &endian);
}

char **map_reading(char **av, t_data *data)
{
    char    **map;
    int     fd;
    char    *line;
    int     rows;
    size_t     cols;
	int i;

	i = -1;
    rows = 0;
    fd = open(av[1], O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        rows++;
        free(line);
    }
    data->map_rows = rows;
    printf("%d\n", rows);
    data->map_cols = 0;
    close(fd);
    map = (char**)malloc(sizeof(char*) * rows);
    fd = open(av[1], O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        cols = ft_strlen(line);
        if ((int)cols > data->map_cols)
            data->map_cols = (int)cols;
        map[++i] = (char*)malloc(sizeof(char) * cols + 1);
        ft_strcpy(map[i], line);
        map[i][cols] = '\0';
        printf("%s\n", map[i]);
        free(line);
    }
    return (map);
}


void	skybox(t_data *data)
{
	int index;
	int x = -1;
	int y = -1;

	while (++y < data->ppc && y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			index = (x + y * WIDTH) * 4;
			data->img_data[index] = mlx_get_color_value(data->mlx_ptr, 255);
			data->img_data[index + 1] = mlx_get_color_value(data->mlx_ptr, 205);
			data->img_data[index + 2] = mlx_get_color_value(data->mlx_ptr, y * (255) / (data->ppc));
		}
	}
}

void	floorbox(t_data *data)
{
	int index;
	int x = -1;
	int y = data->ppc;

	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			index = (x + y * WIDTH) * 4;
			data->img_data[index] = mlx_get_color_value(data->mlx_ptr, 67);
			data->img_data[index + 1] = mlx_get_color_value(data->mlx_ptr, 109);
			data->img_data[index + 2] = mlx_get_color_value(data->mlx_ptr, 74);
		}
	}
}

void    crosshair(t_data *data)
{
    t_point start;
    t_point end;

    set_color(data, 0, 0, 0);
    start.x = WIDTH / 2 - 15;
    start.y = HEIGHT / 2 - 1;
    end.x = WIDTH / 2 + 15;
    end.y = start.y;
    while (start.y < HEIGHT / 2 + 2)
    {
        put_line(start, end, *data);
        start.y++;
        end.y++;
    }
    start.x = WIDTH / 2 - 1;
    start.y = HEIGHT / 2 - 15;
    end.x = start.x;
    end.y = HEIGHT / 2 + 15;
    while (start.x < WIDTH / 2 + 2)
    {
        put_line(start, end, *data);
        start.x++;
        end.x++;
    }
    set_color(data, 255, 255, 255);
}

void	dogening(t_data *data)
{
	int x;
	int y;

	y = -1;
	while (++y < data->map_rows)
	{
		x = -1;
		while (++x < data->map_cols)
		{
			if (data->map[y][x] != '0')
				data->map[y][x] = 'a';
		}
	}
}

void	undogening(t_data *data)
{
	int x;
	int y;

	y = -1;
	while (++y < data->map_rows)
	{
		x = -1;
		while (++x < data->map_cols)
		{
			if (data->map[y][x] == 'a')
				data->map[y][x] = '1';
		}
	}
}

int		exit_x(void *par)
{
	par = NULL;
	exit(42);
	return (0);

}

void	rooms(t_data *data)
{
	if (data->px / data->cell_size < 20 || data->py  / data->cell_size < 15
		|| data->px / data->cell_size > 34 || data->py  / data->cell_size > 18)
		clear_window(*data, 0, 0, 0, 0);
	if (data->px / data->cell_size >= 20 && data->py  / data->cell_size >= 2
		&& data->px / data->cell_size <= 34 && data->py  / data->cell_size <= 5) {
		clear_window(*data, 0, 0, 0, 0);
	}
	else if (data->px / data->cell_size >= 20 && data->py  / data->cell_size >= 9
			 && data->px / data->cell_size <= 34 && data->py  / data->cell_size <= 12) {
		clear_window(*data, 255, 255, 255, 240);
		usleep(30000);
	}
	else if (data->px / data->cell_size >= 20 && data->py  / data->cell_size >= 15
			 && data->px / data->cell_size <= 34 && data->py  / data->cell_size <= 18)
		;
	else
	{
		skybox(data);


	}
}

int		loop_hook(void *param)
{
    t_data *data;
    data = (t_data*)param;
	clear_window(*data, 0, 0, 0, 0);
	if (data->rooms)
		rooms(data);
	if (data->debug % 2 == 0)
		draw_grid(*data);
	ray_casting(data);
	crosshair(data);
	set_color(data, 255, 255, 255);
    set_color(data, 255, 255, 255);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
    return (0);
}

int main(int ac, char **av)
{
    t_data data;
    int bpp;
    int endian;
    int size_line;
    int i = -1;
    int j;

    is_error(ac, av);
    rx = 0;
    ry = 500;
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "lol");
    data.img_ptr = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
    data.img_data = mlx_get_data_addr(data.img_ptr, &bpp, &size_line, &endian);
    data.cell_size = 10000;
    data.debug = 1;
    data.pov = 45.0f;
    data.fov = 76;
    data.tx_index = 0;
    data.speed = data.cell_size / 6;
    crt_animation(&data);
    crt_textures(av, ac, &data);
    crt_floor_and_ceiling_tex(&data);
    data.map = map_reading(av, &data);
    if (!strcmp(av[1], "rooms"))
    	data.rooms = 1;
    else
    	data.rooms = 0;
    j = -1;
    while (++i < data.map_rows)
	{
		j = -1;
		while (++j < data.map_cols)
			if (data.map[i][j] == '0')
				break;
		if (data.map[i][j] == '0')
			break;
	}
	data.px = j * data.cell_size + data.cell_size / 2;
	data.py = i * data.cell_size + data.cell_size / 2;
	printf("y:%f\nx:%f\n", data.py / data.cell_size, data.px / data.cell_size);
	data.ppc = HEIGHT / 2;
	mlx_hook(data.win_ptr, 2, 4, key_hook, &data);
    mlx_loop_hook(data.mlx_ptr, loop_hook, &data);
	mlx_hook(data.win_ptr, 6, 0, motion_hook, &data);
	mlx_hook(data.win_ptr, 17, 1L << 17, exit_x, &data);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	mlx_loop(data.mlx_ptr);
    return (0);
}
