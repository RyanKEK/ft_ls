/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 15:03:14 by ohavryle          #+#    #+#             */
/*   Updated: 2019/04/07 15:03:16 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int cell_size = 60;

//void	floor_casting(t_data *data, int x, double wall_dist, t_fpoint wall, int bottom)
//{
//	int texy;
//	double y;
//
//	y = bottom;
//	while (++y < HEIGHT)
//	{
//		texy = (y - bottom) /  (HEIGHT - bottom) * (data->floor_h)
//
//
//
//
//
//
//
//	}
//
//}

void    floor_casting(t_data *data, int x, double wall_dist, t_fpoint wall, int bottom, double right_angle)
{
    double dist;
    double weight;
    t_fpoint floor;
    t_fpoint floor_tex;
    double y;
	int index;
	int tindex;
	double tex_w = 100.0;
	double tex_h = 100.0;
    y = bottom - 1;
    while (++y < HEIGHT)
	{
    	dist = HEIGHT / (2.0 * (y + ((HEIGHT / 2.0) - data->ppc)) - HEIGHT);
    	//dist = HEIGHT / (2.0 * y - HEIGHT);
    	dist /= cos(right_angle * RAD);
    	weight = (dist - 0.0) / ((wall_dist / data->cell_size) - 0.0);
		floor.x = weight * (wall.x / data->cell_size) + (1.0 - weight) * (data->px / data->cell_size);
    	floor.y = weight * (wall.y /data->cell_size) + (1.0 - weight) * (data->py / data->cell_size);
    	floor_tex.x = (int)(floor.x * tex_w) % data->floor_w;
    	floor_tex.y = (int)(floor.y * tex_h) % data->floor_h;
    	index = (x + (int)y * WIDTH) * 4;
		tindex = ((int)floor_tex.x + (int)floor_tex.y *	data->floor_w) * 4;
		data->img_data[index] = data->floor_data[tindex];
		data->img_data[index + 1] = data->floor_data[tindex + 1];
		data->img_data[index + 2] = data->floor_data[tindex + 2];
	}
}

void	ceiling_casting(t_data *data, int x, double wall_dist, t_fpoint wall, int top, double right_angle)
{
	double dist;
	double weight;
	t_fpoint ceiling;
	t_fpoint ceiling_tex;
	double y;
	int index;
	int tindex;
	y = top;
	while (--y > 0)
	{
		//dist = HEIGHT / (2.0 * (y + ((HEIGHT / 2.0) - data->ppc)) - HEIGHT);
		dist = HEIGHT / (HEIGHT - 2.0 * (y + ((HEIGHT / 2.0) - data->ppc)));
		dist /= cos(right_angle * RAD);
		weight = (dist - 0.0) / ((wall_dist / data->cell_size) - 0.0);
		ceiling.x = weight * (wall.x / data->cell_size) + (1.0 - weight) * (data->px / data->cell_size);
		ceiling.y = weight * (wall.y /data->cell_size) + (1.0 - weight) * (data->py / data->cell_size);
		ceiling_tex.x = (int)(ceiling.x * data->ceiling_w) % data->ceiling_w;
		ceiling_tex.y = (int)(ceiling.y * data->ceiling_h) % data->ceiling_h;
		index = (x + (int)y * WIDTH) * 4;
		tindex = ((int)ceiling_tex.x + (int)ceiling_tex.y *	data->ceiling_w) * 4;
		data->img_data[index] = data->ceiling_data[tindex];
		data->img_data[index + 1] = data->ceiling_data[tindex + 1];
		data->img_data[index + 2] = data->ceiling_data[tindex + 2];
	}
}

void	line_texturing(int start, int end, double tx, int x, t_data *data)
{
	double ty;
	int index;
	int tindex;
	int y;
    double intensity;

    if (start - end < HEIGHT / 5)
	    intensity = 150;
	else if (start - end < HEIGHT / 4)
	    intensity = 100;
    else if (start - end < HEIGHT / 3)
        intensity = 50;
    else
        intensity = 0;
    tx = tx / data->cell_size * data->w[data->tx_index];
	y = end;
	ty = 0;
	while (y < start)
	{
		index = (x + y * WIDTH) * 4;
		tindex = ((int)tx + (int)ty * data->w[data->tx_index]) * 4;
		if (index + 2 < ((WIDTH - 1) + (HEIGHT - 1) * WIDTH) * 4 && index > 0
			&& tindex < ((data->w[data->tx_index] - 1) + data->h[data->tx_index] - 1) * data->w[data->tx_index] * 4 && tindex > 0)
		{
			data->img_data[index] = data->tx_datas[data->tx_index][tindex];
			data->img_data[index + 1] = data->tx_datas[data->tx_index][tindex + 1];
			data->img_data[index + 2] = data->tx_datas[data->tx_index][tindex + 2];
		}
		ty += (double)data->h[data->tx_index] / abs(start - end);
		y++;
	}
}

void	wall_render(t_fpoint h, t_fpoint v, t_data *data, double right_angle, int cp)
{
	double h_intersec;
	double v_intersec;
	double height;
	t_point start;
	t_point end;

	h_intersec = sqrt((data->px - h.x) * (data->px - h.x) + (data->py - h.y) * (data->py - h.y));
	v_intersec = sqrt((data->px - v.x) * (data->px - v.x) + (data->py - v.y) * (data->py - v.y));
	if ((h_intersec >= v_intersec || (int)h_intersec < 0) && (int)v_intersec > 0)
	{
		height = (double)data->cell_size / v_intersec * ((WIDTH / 2.0) / tan((data->fov / 2.0) * RAD));
		if (data->textures > 0)
			data->tx_index = data->map[(int)v.y / data->cell_size][(int)v.x / data->cell_size] - 49;
		else
		{
			if (data->rounded_angle < 90 || data->rounded_angle > 270)
				data->tx_index = 1;
			else
				data->tx_index = 3;
		}
	}
	else{
		height = (double)data->cell_size / h_intersec * ((WIDTH / 2.0) / tan((data->fov / 2.0) * RAD));
		if (data->textures > 0)
			data->tx_index = data->map[(int)h.y / data->cell_size][(int)h.x / data->cell_size] - 49;
		else
		{
			if (data->rounded_angle > 180)
				data->tx_index = 0;
			else
				data->tx_index = 2;
		}
	}
	height = (height / cos(-right_angle * RAD));
	end.x = cp;
	start.x = cp;
	start.y = data->ppc + (int)height / 2;
	end.y = data->ppc - (int)height / 2;
	if ((h_intersec > v_intersec || (int)h_intersec < 0) && (int)v_intersec > 0)
	{
		if (data->map[(int)v.y / data->cell_size][(int)v.x / data->cell_size] == 'a')
			animation_texturing(start.y, end.y, (int)v.y % data->cell_size, cp, data);
		else
			line_texturing(start.y, end.y, (int)v.y % data->cell_size, cp, data);
		floor_casting(data, cp, v_intersec, v, start.y, right_angle);
		ceiling_casting(data, cp, v_intersec, v, end.y, right_angle);
	}
	else {
		if (data->map[(int)h.y / data->cell_size][(int)h.x / data->cell_size] == 'a')
			animation_texturing(start.y, end.y, (int)h.x % data->cell_size, cp, data);
		else
			line_texturing(start.y, end.y, (int)h.x % data->cell_size, cp, data);
		floor_casting(data, cp, h_intersec, h, start.y, right_angle);
		ceiling_casting(data, cp, h_intersec, h, end.y, right_angle);
	}
}

void    critical_angles(t_fpoint *horiz, t_fpoint *vert, t_data *data)
{
	if ((data->rounded_angle < 10 || data->rounded_angle > 350) && horiz->x < data->px)
	{
		horiz->x = vert->x + 1;
		horiz->y = vert->y + 1;
	}
	else if (data->rounded_angle > 170 && data->rounded_angle < 190 && horiz->x > data->px)
	{
		horiz->x = vert->x - 1;
		horiz->y = vert->y - 1;
	}
	else if (data->rounded_angle > 80 && data->rounded_angle < 100 && vert->y < data->py)
	{
		vert->x = horiz->x + 1;
		vert->y = horiz->y + 1;
	}
	else if (data->rounded_angle < 280 && data->rounded_angle > 260 && vert->y > data->py)
	{
		vert->x = horiz->x - 1;
		vert->y = horiz->y - 1;
	}
}

t_fpoint	check_and_proceed(t_fpoint current, t_fpoint next, t_data *data)
{
	while (1)
	{
		if (current.y / data->cell_size < 0 || current.y / data->cell_size >= data->map_rows
			|| current.x / data->cell_size < 0 || current.x / data->cell_size >= data->map_cols) {
			break ;
		}
		if (data->map[(int)(current.y / data->cell_size)][(int)(current.x / data->cell_size)] != '0')
			break ;
		current.x = current.x + next.x;
		current.y = current.y + next.y;
	}
	return (current);
}

void	first_inter(t_fpoint *inter, t_fpoint *next, t_data *data, char side)
{
	if (side == 'h')
	{
		if (data->rounded_angle > 180)
			inter->y = (int)(data->py / data->cell_size) * data->cell_size - 1;
		else
			inter->y = (int)(data->py / data->cell_size) * data->cell_size + data->cell_size;
		inter->x = data->px + (data->py - inter->y) / tan(-data->angle * RAD);
		if (data->rounded_angle > 180)
			next->y = -data->cell_size;
		else
			next->y = data->cell_size;
		next->x = next->y / tan(data->angle * RAD);
	}
	else
	{
		if (data->rounded_angle < 90 || data->rounded_angle > 270)
			inter->x = (int) (data->px / data->cell_size) * data->cell_size + data->cell_size;
		else
			inter->x = (int) (data->px / data->cell_size) * data->cell_size - 1;
		inter->y = data->py + (data->px - inter->x) * tan(-data->angle * RAD);
		if (data->rounded_angle < 90 || data->rounded_angle > 270)
			next->x = data->cell_size;
		else
			next->x = -data->cell_size;
		next->y = next->x * tan(data->angle * RAD);
	}
}

void	ray_casting(t_data *data)
{
	t_fpoint	v_nearest;
	t_fpoint	h_nearest;
	t_fpoint	next;
	int			cp;
	double		right_angle;
	right_angle = -(data->fov / 2);
	cp = -1;
	data->angle = data->pov - (data->fov / 2);
	while (++cp < WIDTH)
	{
		data->rounded_angle = (360 + ((int)data->angle % 360)) % 360;
		first_inter(&h_nearest, &next, data, 'h');
		h_nearest = check_and_proceed(h_nearest, next, data);
		first_inter(&v_nearest, &next, data, 'v');
		v_nearest = check_and_proceed(v_nearest, next, data);
		critical_angles(&h_nearest, &v_nearest, data);
		wall_render(h_nearest, v_nearest, data, right_angle, cp);
		data->angle += data->fov / WIDTH;
		right_angle += data->fov / WIDTH;
	}
}
