/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:24:10 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/17 15:30:51 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Change the color of a pixel at given coords.
void	my_mlx_pixel_put(t_mlximg *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W - 60 || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// Creates a new image for mlx library.
void	img_new(t_mlx *mlx)
{
	mlx->img.img = mlx_new_image(mlx->mlx, WIN_W - 60, WIN_H);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
}

// wave(mlx);
// Draw the map and icons depending on the active view.
void	img_draw(t_mlx *mlx)
{
	mlx->ui.cam = mlx->cam;
	mlx->ui.cam.zoom = 1;
	if (mlx->cam.view == 1)
	{
		proy_iso(&mlx->map, &mlx->cam, 1, mlx);
		proy_iso(&mlx->ui.cube_map, &mlx->ui.cam, 1, mlx);
	}
	else if (mlx->cam.view == 0)
	{
		proy_conic(mlx, &mlx->map, &mlx->cam, 1);
		proy_iso(&mlx->ui.cone_map, &mlx->ui.cam, 1, mlx);
	}
	else
	{
		proy_iso(&mlx->sphere, &mlx->cam, 1, mlx);
		proy_iso(&mlx->ui.sphere_map, &mlx->ui.cam, 1, mlx);
	}
	if (mlx->ui.rgbcircle)
		color_rgb(mlx, 0, 0, mlx->ui.rgbcircle);
	circle_draw(mlx, mlx->map.colormin, 25, WIN_H - 25);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	put_data(mlx);
}

// Another version to clean all the maps, better for small maps.
/*void	img_clean(t_mlx *mlx)
{
	int	x;
	int	y;

	mlx->p--;
	while (mlx->p > 1)
	{
		y = mlx->cleaner[mlx->p--];
		x = mlx->cleaner[mlx->p];
		my_mlx_pixel_put(&mlx->img, x, y, 0);
	}
}*/

// Clean the entire image to black.
void	img_clean(t_mlx *mlx)
{
	t_point	p;

	p.x = -1;
	while (++p.x < WIN_W - 60)
	{
		p.y = -1;
		while (++p.y < WIN_H)
			my_mlx_pixel_put(&mlx->img, p.x, p.y, 0);
	}
}

// Recalculate map to paint it black (to be optimized).
/*color_rgb(mlx, 0, 0, mlx->ui.rgbcircle);
mlx->ui.cam = mlx->cam;
mlx->ui.cam.zoom = 1;
if (mlx->cam.view == 1)
{
	proy_iso(&mlx->map, &mlx->cam, 0, mlx);
	proy_iso(&mlx->ui.cube_map, &mlx->ui.cam, 0, mlx);
}
else if (mlx->cam.view == 0)
{
	proy_conic(mlx, &mlx->map, &mlx->cam, 0);
	proy_iso(&mlx->ui.cone_map, &mlx->ui.cam, 0, mlx);
}
else
{
	proy_iso(&mlx->sphere, &mlx->cam, 0, mlx);
	proy_iso(&mlx->ui.sphere_map, &mlx->ui.cam, 0, mlx);
}*/

// void	proy_iso(t_map *m, t_cam *cam, t_mlximg *img, int trgb)
// Isometric projection
void	proy_iso(t_map *m, t_cam *cam, int trgb, t_mlx *mm)
{
	int		i;
	t_point	a;
	t_point	b;

	map_limits(m);
	i = 0;
	while (i < m->size)
	{
		// b = point_move(m, i, point_fill(-(m->max.x - m->min.x) / 2,
		// 			-(m->max.y - m->min.y) / 2, 0));
		b = point_move(m, i, point_fill(0, 0, 0));
		b = point_project(cam, b, m->gap.x, m->gap.y);
		if (i > 0 && (i % (m->height + 1) && check_paint(m, cam, i, b))
			&& !point_overlap(a, b))
			line (mm, a, b, trgb * fmax(m->xyzc[i][3], m->xyzc[i - 1][3]));
		a = b;
		if (i + m->height + 1 < m->size && check_paint(m, cam, i, b))
		{
			// b = point_move(m, i + m->height + 1, point_fill(-(m->max.x
			// 				- m->min.x) / 2, -(m->max.y - m->min.y) / 2, 0));
			b = point_move(m, i + m->height + 1, point_fill(0, 0, 0));
			b = point_project(cam, b, m->gap.x, m->gap.y);
			line(mm, a, b, trgb * fmax(m->xyzc[i][3],
					m->xyzc[i + m->height + 1][3]));
		}
		i++;
	}
}
