/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:12:06 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/25 18:19:17 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_W	1080
# define WIN_H	720
# define MAP_SIZE 520

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <math.h>
#include <limits.h>

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}				t_img;

typedef struct	s_point {
	double	x;
	double	y;
	double	z;
}				t_point;

typedef struct	s_map {
	char *dir;
	int	width;
	int	height;
	int	size;
	int	colormin;
	int	colormax;
	t_point	max;
	t_point	min;
	int	cmax[3];
	int	cmin[3];
	int	**xyzc;
}				t_map;

typedef struct	s_cam {
	double		zoom;
	int		auto_rot;
	int		auto_rotv;
	double	angleh;
	double	anglev;
	int		view;
	double	dist;
	t_point	pos;
}				t_cam;

typedef struct	s_mouse {
	int	l;
	int	r;
	int	x;
	int	y;
}				t_mouse;

typedef struct	s_line {
	t_point	ini;
	t_point	fin;
	double	xo;
	double	yo;
	double	xf;
	double	yf;
}				t_line;

typedef struct	s_ui {
	int	rgbcircle;
	void	**Button;
	char	*Button_file;
	int		frame;
	int		time;
	int		mouse_in;
	int		x;
	int		y;
	t_cam	cube_cam;
	t_map	cube_map;
	t_cam	cone_cam;
	t_map	cone_map;
}				t_ui;

typedef struct	s_color {
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct	s_mlx {
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	map;
	t_cam	cam;
	t_mouse	mouse;
	t_line	line;
	t_ui	ui;
}				t_mlx;

int		hook_keydown(int key, t_mlx *mlx);
int 	hook_mousemove(int x, int y, t_mlx *mlx);
int		hook_mousedown(int button, int x, int y, t_mlx *mlx);
int		hook_mouseup(int button, int x, int y, t_mlx *mlx);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	img_fill(t_map *map, t_cam *cam, t_img *img, int gapx, int gapy, int trgb);
void	img_new(t_mlx *mlx);
void	img_clean(t_mlx *mlx);
void	img_draw(t_mlx *mlx);
int		atoi_hexa(char* str);
void	cube_draw(t_map *map);
int		hook_rotate(t_mlx *mlx);
void	circle_draw(t_mlx *mlx, int color, int x, int y);
int		color_rgb(t_mlx *mlx, int getx, int gety, int d);
int		color_pick(t_img *img, int x, int y);
void	map_fill(t_map *map, char *dir);
int		map_deltaz(t_map *map);
void	map_color(t_map *map);
void	map_repaint(t_map *map);
int		trgb(int t, int r, int g, int b);
double	rotz(t_cam *cam, double x, double y, double xy);
double	rotx(t_cam *cam, double y, double z);
void	line(t_img *img, t_point a, t_point b, int trgb);
t_point	point_move(t_map *m, int point, int dx, int dy, int dz);
t_point	point_project(t_cam *cam, t_point a, int gapx, int gapy);
void	fdf_init(t_mlx *mlx, char *dir);
t_point cam_pos(t_cam *cam);
void	cam_rayo(t_mlx *mlx, t_map *map, t_cam *cam, int trgb);
void	map_limits(t_map *m);
void	Button_load(t_mlx *mlx);
void	Button_draw(t_mlx *mlx);
void	put_data(t_mlx *mlx);
void	update_value(t_mlx *mlx, double *val, double dv, double max);
#endif
