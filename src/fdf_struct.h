/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:04:46 by jvasquez          #+#    #+#             */
/*   Updated: 2022/11/16 11:53:28 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCT_H
# define FDF_STRUCT_H

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_point {
	float	x;
	float	y;
	float	z;
	int		c;
}				t_point;

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

typedef struct s_button {
	int		id;
	char	*text;
	t_point	center;
}				t_button;

typedef struct s_menu {
	t_button	button[8];
	int			size;
	int			hover_on;
}				t_menu;

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

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	int		*cleaner;
	int		p;
	t_img	img;
	t_map	map;
	t_map	sphere;
	t_cam	cam;
	t_mouse	mouse;
	t_ui	ui;
}				t_mlx;
#endif
