/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:55:05 by ohavryle          #+#    #+#             */
/*   Updated: 2019/03/27 14:55:06 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int cell_sized = 60;

void    set_color(t_data *data, int r, int g, int b)
{
    data->color.r = r;
    data->color.g = g;
    data->color.b = b;
}

void    draw_grid(t_data data)
{
	t_point start;
	t_point player;
	t_point ray;

	player.x = data.px * (data.map_cols* cell_sized) / (data.map_cols * data.cell_size);
	player.y = data.py * (data.map_rows* cell_sized) / (data.map_rows * data.cell_size);
	start.x = 0;
	start.y = 0;
	while (start.y < data.map_rows* cell_sized)
	{
		start.x = 0;
		while (start.x / cell_sized < (int)(ft_strlen(data.map[start.y / cell_sized])))
		{
			if (data.map[start.y / cell_sized][start.x / cell_sized] != '0')
			{
                set_color(&data, 0, 0, 255);
                fill_rect(start, cell_sized + 1, cell_sized + 1, data);
                set_color(&data, 255, 255, 255);
			}
			rect(start, cell_sized, cell_sized, data);
			start.x += cell_sized;
		}
		start.y += cell_sized;
	}
	ray.x = (int)(1000 * cos(data.pov  * RAD)) + player.x;
	ray.y = (int)(1000 * sin(data.pov  * RAD)) + player.y;
	set_color(&data, 255, 255, 0);
	put_line(player, ray, data);
	rect(player, 5, 5, data);
	set_color(&data, 255, 255, 255);
}
