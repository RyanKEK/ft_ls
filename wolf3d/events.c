/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:35:03 by ohavryle          #+#    #+#             */
/*   Updated: 2019/03/27 14:35:04 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		motion_hook(int x, int y, void *param)
{
	t_data	*data;
	static int tmpx = 0;
	static int c = 0;
	static int tmpy = 0;

	data = (t_data *) param;
	if (1)
	{
		if (c == 0) {
			tmpy = y;
			tmpx = x;
		}
		data->pov += (x - tmpx) / 5.0;
		data->ppc -= (y - tmpy) * 2;
		if (data->ppc > HEIGHT + HEIGHT / 2)
			data->ppc = HEIGHT + HEIGHT / 2;
		tmpy = y;
		tmpx = x;
		c++;
	}
	return (0);
}
int		key_hook(int keycode, void *param)
{
	t_data *data;

	//printf("keycode:%d\n", keycode);
	data = (t_data *)param;
	if (keycode == 53)
		exit(42);
	else if (keycode == 15)
	    data->fov = 60;
	else if (keycode == 257)
	{
		if (data->speed == data->cell_size / 6)
			data->speed = data->cell_size / 3;
		else
			data->speed = data->cell_size / 6;
	}
	else if (keycode == 0)
		data->pov -= 5;
	else if (keycode == 2)
		data->pov += 5;
	else if (keycode == 123)
	{
		data->px = (int)(data->speed * cos((data->pov - 90) * RAD)) + data->px;
		data->py = (int)(data->speed * sin((data->pov - 90) * RAD)) + data->py;
	}
	else if (keycode == 124)
	{
		data->px = (int)(data->speed * cos((data->pov + 90) * RAD)) + data->px;
		data->py = (int)(data->speed * sin((data->pov + 90) * RAD)) + data->py;
	}
	else if (keycode == 13 || keycode == 126)
	{
		if (data->map[((int)(data->speed * 2 * sin(data->pov * RAD) + data->py)) / data->cell_size][((int)(data->speed * 2 * cos(data->pov * RAD) + data->px)) / data->cell_size] != '0')
	        return (0);
	    data->px = (int)(data->speed * cos(data->pov * RAD)) + data->px;
		data->py = (int)(data->speed * sin(data->pov * RAD)) + data->py;
	}
	else if (keycode == 1 || keycode == 125)
	{
        if (data->map[((int)(-data->speed * 2 * sin(data->pov * RAD) + data->py)) / data->cell_size][((int)(-data->speed * 2 * cos(data->pov * RAD) + data->px)) / data->cell_size] != '0')
            return (0);
	    data->px = (int)(-data->speed * cos(data->pov * RAD)) + data->px;
		data->py = (int)(-data->speed * sin(data->pov * RAD)) + data->py;
	}
	else if (keycode == 11)
		data->debug++;
	else if (keycode == 256)
	{
		if (data->ppc == HEIGHT / 2)
			data->ppc -= 30;
		else
			data->ppc = HEIGHT / 2;
	}
	return (0);
}

int		mouse_hook(int button, int x, int y,  void *param)
{
	t_data *data;
    double nx;
    double ny;

	data = (t_data *)param;
	x = 0;
	y = 0;
	if (y < 0)
		printf("asdasd\n");
	if (button == 1 && data->textures > 0)
	{
        nx = data->px;
        ny = data->py;
	    while (data->map[(int)ny / data->cell_size][(int)nx / data->cell_size] == '0')
        {
	        nx = 2 * cos(data->pov * RAD) + nx;
            ny = 2 * sin(data->pov * RAD) + ny;
        }
        if (data->map[(int)ny / data->cell_size][(int)nx
        / data->cell_size] < data->textures + 48)
	        data->map[(int)ny / data->cell_size][(int)nx / data->cell_size]++;
	    else
            data->map[(int)ny / data->cell_size][(int)nx / data->cell_size] = '1';
	    //printf("ny:%d\nnx:%d\n", (int)ny / data->cell_size, (int)nx / data->cell_size);
	}
	else if (button == 4)
	    data->fov++;
	else if (button == 5)
	    data->fov--;
	if (data->fov < 40)
		data->fov = 40;
	else if (data->fov > 120)
		data->fov = 120;
	return (0);
}
