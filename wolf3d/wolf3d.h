/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:54:12 by ohavryle          #+#    #+#             */
/*   Updated: 2019/02/28 16:54:13 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define WIDTH 800
# define HEIGHT 600
# include <stdio.h>
# include "libft/libft.h"
#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
# define RAD 0.0174533

typedef struct	s_point
{
    int x;
    int y;
}				t_point;

typedef struct	s_color
{
	int r;
	int g;
	int b;
}				t_color;

typedef struct	s_fpoint
{
	double x;
	double y;
}				t_fpoint;

typedef struct	s_texture
{
	int		w;
	int		h;
	void	*tx_ptr;
	char 	*tx_data;
}				t_texture;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	t_color	color;
	char	**map;
	double	pov;
	double	fov;
	int		cell_size;
	int		map_rows;
	int 	map_cols;
	int 	debug;
	double	px;
	double	py;
	int		ppc;
	int 	speed;
	void	**tx_ptrs;
	char 	**tx_datas;
	int 	tx_index;
	int 	w[9];
	int		h[9];
    void	**an_ptrs;
    char 	**an_datas;
    int 	an_w[16];
    int		an_h[16];
    int		textures;
    double	angle;
    int 	rounded_angle;
    int 	rooms;
    void	*floor_tex;
    char	*floor_data;
    int 	floor_w;
    int		floor_h;
	void	*ceiling_tex;
	char	*ceiling_data;
	int 	ceiling_w;
	int		ceiling_h;
}				t_data;


int		get_next_line(const int fd, char **line);
int		motion_hook(int x, int y, void *param);
int		key_hook(int keycode, void *param);
void	draw_grid(t_data data);
void	pixel_put(int x, int y, t_data data);
void	put_line(t_point start, t_point end, t_data data);
void	rect(t_point point, int width, int height, t_data data);
void	fill_rect(t_point point, int width, int height, t_data data);
void    set_color(t_data *data, int r, int g, int b);
int		mouse_hook(int button, int x, int y,  void *param);
void	ray_casting(t_data *data);
void	crt_animation(t_data *data);
void	animation_texturing(int start, int end, int tx, int x, t_data *data);
void	is_error(int ac, char **av);


#endif
