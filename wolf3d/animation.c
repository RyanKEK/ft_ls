/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:47:20 by ohavryle          #+#    #+#             */
/*   Updated: 2019/04/08 12:47:21 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void crt_animation(t_data *data)
{
    int i;
    int bpp;
    int endian;
    int size_line;

    i = -1;
    data->an_ptrs = malloc(sizeof(void*) * 16);
    data->an_datas = malloc(sizeof(char*) * 16);
    data->an_ptrs[0] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame1", &data->an_w[0], &data->an_h[0]);
    data->an_datas[0] = mlx_get_data_addr(data->an_ptrs[0], &bpp, &size_line, &endian);
    data->an_ptrs[1] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame2", &data->an_w[1], &data->an_h[1]);
    data->an_datas[1] = mlx_get_data_addr(data->an_ptrs[1], &bpp, &size_line, &endian);
    data->an_ptrs[2] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame3", &data->an_w[2], &data->an_h[2]);
    data->an_datas[2] = mlx_get_data_addr(data->an_ptrs[2], &bpp, &size_line, &endian);
    data->an_ptrs[3] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame4", &data->an_w[3], &data->an_h[3]);
    data->an_datas[3] = mlx_get_data_addr(data->an_ptrs[3], &bpp, &size_line, &endian);
    data->an_ptrs[4] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame5", &data->an_w[4], &data->an_h[4]);
    data->an_datas[4] = mlx_get_data_addr(data->an_ptrs[4], &bpp, &size_line, &endian);
    data->an_ptrs[5] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame6", &data->an_w[5], &data->an_h[5]);
    data->an_datas[5] = mlx_get_data_addr(data->an_ptrs[5], &bpp, &size_line, &endian);
    data->an_ptrs[6] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame7", &data->an_w[6], &data->an_h[6]);
    data->an_datas[6] = mlx_get_data_addr(data->an_ptrs[6], &bpp, &size_line, &endian);
    data->an_ptrs[7] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame8", &data->an_w[7], &data->an_h[7]);
    data->an_datas[7] = mlx_get_data_addr(data->an_ptrs[7], &bpp, &size_line, &endian);
    data->an_ptrs[8] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame9", &data->an_w[8], &data->an_h[8]);
    data->an_datas[8] = mlx_get_data_addr(data->an_ptrs[8], &bpp, &size_line, &endian);
    data->an_ptrs[9] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame10", &data->an_w[9], &data->an_h[9]);
    data->an_datas[9] = mlx_get_data_addr(data->an_ptrs[9], &bpp, &size_line, &endian);
    data->an_ptrs[10] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame11", &data->an_w[10], &data->an_h[10]);
    data->an_datas[10] = mlx_get_data_addr(data->an_ptrs[10], &bpp, &size_line, &endian);
    data->an_ptrs[11] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame12", &data->an_w[11], &data->an_h[11]);
    data->an_datas[11] = mlx_get_data_addr(data->an_ptrs[11], &bpp, &size_line, &endian);
    data->an_ptrs[12] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame13", &data->an_w[12], &data->an_h[12]);
    data->an_datas[12] = mlx_get_data_addr(data->an_ptrs[12], &bpp, &size_line, &endian);
    data->an_ptrs[13] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame14", &data->an_w[13], &data->an_h[13]);
    data->an_datas[13] = mlx_get_data_addr(data->an_ptrs[13], &bpp, &size_line, &endian);
    data->an_ptrs[14] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame15", &data->an_w[14], &data->an_h[14]);
    data->an_datas[14] = mlx_get_data_addr(data->an_ptrs[14], &bpp, &size_line, &endian);
    data->an_ptrs[15] = mlx_xpm_file_to_image(data->mlx_ptr, "doge/frame16", &data->an_w[15], &data->an_h[15]);
    data->an_datas[15] = mlx_get_data_addr(data->an_ptrs[15], &bpp, &size_line, &endian);
}

void	animation_texturing(int start, int end, int tx, int x, t_data *data)
{
    float ty;
    int index;
    int tindex;
    int y;
    static int frame = 0;
	static clock_t previous;
    static int c = 0;

    if (c == 0)
    {
        c++;
        previous = clock();
    }
    if ((clock() - previous) * 1000 / CLOCKS_PER_SEC >= 30) {
		frame++;
		c = 0;
	}
    if (frame > 15) {
		c = 0;
    	frame = 0;
	}
    tx = (int)((float)tx / (float)data->cell_size * (float)data->an_w[frame]);
    y = end;
    ty = 0;
    while (y < start)
    {
        index = (x + y * WIDTH) * 4;
        tindex = (tx + (int)ty * data->an_w[frame]) * 4;
        if (index + 2 < ((WIDTH - 1) + (HEIGHT - 1) * WIDTH) * 4 && index > 0
            && tindex < ((data->an_w[frame] - 1) + (int)(data->an_h[frame] - 1) * data->an_w[frame]) * 4 && tindex > 0)
        {
            data->img_data[index] = data->an_datas[frame][tindex];
            data->img_data[index + 1] = data->an_datas[frame][tindex + 1];
            data->img_data[index + 2] = data->an_datas[frame][tindex + 2];
        }
        ty += (float)data->an_h[frame] / abs(start - end);
        y++;
    }
}