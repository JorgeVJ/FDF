/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <jvasquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:12:06 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/19 17:02:51 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "X11/keysymdef.h"

#ifndef FDF_H
# define FDF_H
# define WIN_W	    1024
# define WIN_H	    1024
/* # define KEY_A      0
# define KEY_S      1
# define KEY_D      2
# define KEY_Z      6
# define KEY_C      8
# define KEY_V      9
# define KEY_E      14
# define KEY_W      13
# define KEY_Q      12
# define KEY_ESC    53
# define NPD_9      92
# define NPD_8      91
# define NPD_7      89
# define NPD_6      88
# define NPD_5      87
# define NPD_4      86
# define NPD_3      85
# define NPD_2      84
# define NPD_1      83
# define NPD_0      82 */



# define M_LEFT     1
# define M_RIGHT    2
# define M_WUP      4
# define M_WDO      5

# ifdef MACOS
	# include <mlx.h>
# endif

# include "mlx.h"
# include "mlx_int.h"

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "fdf_struct.h"
# include "../UI/menu/mlx_menu.h"
# include "mlx_UI.h"
# include "fdf_map.h"
# include "fdf_utils.h"
# include <math.h>
# include <limits.h>

// void	wave(t_mlx *mlx);
float	scalar(t_point a, t_point b, float max, float min);
float   normalize(t_point *v);
void    normal_generic(t_mlx *m);
void	fdf_init(t_mlx *mlx, char *dir);
void 	reload(t_mlx *m);
void	load_file(t_mlx *m,	char *dir);
int		hook_exit(t_mlx *mlx);
void	my_mlx_pixel_put(t_mlximg *img, int x, int y, int color);
void	line(t_mlx *m, t_point a, t_point b, int trgb);
void	proy_iso(t_map *map, t_cam *cam, int trgb, t_mlx *m);
void	proy_conic(t_mlx *mlx, t_map *map, t_cam *cam, int trgb);
int		check_paint(t_map *map, t_cam *cam, int point, t_point b);
void	img_new(t_mlx *mlx);
void	img_clean(t_mlx *mlx);
void	img_draw(t_mlx *mlx);
void	put_data(t_mlx *mlx);
int		trgb(int t, int r, int g, int b);
int		color_read(char *line, int *pos);
double	rotz(t_cam *cam, double x, double y, double xy);
double	rotx(t_cam *cam, double y, double z);
t_point	point_move(t_map *m, int point, t_point d);
t_point	point_project(t_cam *cam, t_point a, int gapx, int gapy);
int		point_overlap(t_point a, t_point b);
t_point	point_fill(int x, int y, int z);
void	point_create(t_map *map, int point, t_point p);
t_point	get_projected(t_map *m, t_cam *cam, int point);
t_trian	triangle(t_map *map, t_cam *cam, int i);
void	fill_face(t_mlx *mlx, t_trian t);
t_point	normal(t_trian p);
#endif
