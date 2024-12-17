/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:04:46 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/17 15:30:51 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCT_H
# define FDF_STRUCT_H

# include "../UI/menu/mlx_menu.h"
// struct s_button;
// struct s_menu;

typedef struct s_mlximg {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlximg;

/*typedef struct s_point {
	float	x;
	float	y;
	float	z;
	int		c;
}				t_point;*/

typedef struct s_map {
	int		id;
	float	scale;
	int		width;
	int		height;
	int		size;
	int		colormin;
	int		colormax;
	t_point	max;
	t_point	min;
	t_point	gap;
	int		cmax[3];
	int		cmin[3];
	float	**xyzc;
	//t_point *n;
}				t_map;

typedef struct s_cam {
	double		zoom;
	double		angleh;
	double		anglev;
	double		dist;
	double		zscale;
	int			z_key;
	int			auto_rot[4];
	int			view;
	int			param1;
	int			param2;
	t_point		pos;
}				t_cam;

typedef struct s_mouse {
	int	l;
	int	r;
	int	x;
	int	y;
	int	posx;
	int	posy;
}				t_mouse;

typedef struct s_frames {
	void	**images;
	char	*file;
	int		frame;
	int		max;
}				t_frames;

typedef struct s_ui {
	int			rgbcircle;
	t_frames	keys;
	t_frames	logo;
	int			time;
	int			mouse_in;
	char		menu_in;
	t_menu		menu;
	int			x;
	int			y;
	t_cam		cam;
	t_map		cube_map;
	t_map		cone_map;
	t_map		sphere_map;
	int			animation;
	double		a_frame;
}				t_ui;

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_trian {
	t_point	a;
	t_point	b;
	t_point	c;
}				t_trian;

/*typedef struct s_norm {
	t_point	**gen;
}				t_norm;*/

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	int		*cleaner;
	int		p;
	t_mlximg	img;
	t_map	map;
	t_map	sphere;
	t_cam	cam;
	t_mouse	mouse;
	t_ui	ui;
	t_norm	n;
}				t_mlx;
#endif
