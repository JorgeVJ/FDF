/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:12:06 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/30 15:13:00 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_W	1960
# define WIN_H	1024

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
	int	scale;
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
	double		angleh;
	double		anglev;
	double		dist;
	int			auto_rot[4];
	int			view;
	t_point		pos;
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
}				t_line;

typedef struct	s_frames {
	void	**images;
	char	*file;
	int		frame;
	int		max;
}				t_frames;

typedef struct	s_ui {
	int		rgbcircle;
	void	**Button;
	char	*Button_file;
	t_frames keys;
	t_frames logo;
	int		frame;
	int		time;
	int		mouse_in;
	int		x;
	int		y;
	t_cam	cube_cam;
	t_map	cube_map;
	t_cam	cone_cam;
	t_map	cone_map;
	t_map	sphere_map;
	int		animation;
	double	a_frame;
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
void	proy_iso(t_map *map, t_cam *cam, t_img *img, int gapx, int gapy, int trgb);
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
void	put_data(t_mlx *mlx);
int		trgb(int t, int r, int g, int b);
double	rotz(t_cam *cam, double x, double y, double xy);
double	rotx(t_cam *cam, double y, double z);
void	line(t_img *img, t_point a, t_point b, int trgb);
t_point	point_move(t_map *m, int point, int dx, int dy, int dz);
t_point	point_project(t_cam *cam, t_point a, int gapx, int gapy);
void	fdf_init(t_mlx *mlx, char *dir);
t_point cam_pos(t_cam *cam);
void	proy_conic(t_mlx *mlx, t_map *map, t_cam *cam, int trgb);
void	map_limits(t_map *m);
void	update_value_up(t_mlx *mlx, double *val, double dv, double max);
void	update_value_down(t_mlx *mlx, double *val, double dv, double min);
int		**add_point(int **points, int	size, t_point p, int rgb);
void	fill_one(t_map *map, char **datos);
void	fill_two(t_map *map, char **datos);
void	fill_four(t_map *map, char **datos);
int		datos_len(char **datos);
void	proyections(t_mlx *mlx, int	key);
int		point_overlap(t_point a, t_point b);
void	create(t_mlx *mlx);
void	sphere_transform(t_mlx *mlx);
void	map_scale(t_map *map, float scale);
void	images_load(t_mlx *mlx, t_frames *images, char *file, int frames);
void	image_animate(t_mlx *mlx, t_frames *images, int x, int y);
void	key_put(t_mlx *mlx, char *str, int x, int y);
void	key_help(t_mlx *mlx);
void	str_be_free(char *str);
void	ptr_be_free(char **str);
void	rotations_off(t_mlx *mlx);
char	*join_free(char *a, char *b);
void	map_free(int **map);
#endif
