/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_menu.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 12:46:56 by jvasquez          #+#    #+#             */
/*   Updated: 2022/12/17 12:46:57 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_MENU_H
# define MLX_MENU_H

// # include "../../src/fdf_struct.h"
// # include "../../src/fdf.h"
typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_point {
	float	x;
	float	y;
	float	z;
	int		c;
}				t_point;

/*typedef struct s_wpoint {
	int	x;
	int	y;
}				t_wpoint;*/

typedef struct s_button {
	int		id;
	char	*text;
	t_point	dim;
	t_point	center;
	t_point	**nm;
}				t_button;

typedef struct s_norm {
	t_point	**gen;
}				t_norm;

typedef struct s_menu {
	void		*mlx;
	void		*win;
	void		*img;
	t_button	button[8];
	int			size;
	int			hover_on;
	t_point		mouse;
	t_norm		n;
}				t_menu;

//	void    normal_generic(t_mlx *m);
#endif