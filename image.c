/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:24:10 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/25 16:45:32 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W - 60 || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	img_new(t_mlx *mlx)
{
	mlx->img.img = mlx_new_image(mlx->mlx, WIN_W - 60, WIN_H);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	img_draw(mlx);
}

void	img_draw(t_mlx *mlx)
{
		mlx->ui.cube_cam = mlx->cam;
		mlx->ui.cube_cam.zoom = 5;
	if (mlx->cam.view)
	{
		img_fill(&mlx->map, &mlx->cam, &mlx->img, mlx->img.x, mlx->img.y, 1);
		img_fill(&mlx->ui.cube_map, &mlx->ui.cube_cam, &mlx->img, 35, 50, 1);
	}
	else
	{
		cam_rayo(mlx, &mlx->map, &mlx->cam, 1);
		img_fill(&mlx->ui.cone_map, &mlx->ui.cube_cam, &mlx->img, 35, 50, 1);
	}
		
	if (mlx->ui.rgbcircle)
		color_rgb(mlx, 0, 0, mlx->ui.rgbcircle);
	circle_draw(mlx, mlx->map.colormin, 25, WIN_H - 25);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	put_data(mlx);
}

void	img_clean(t_mlx *mlx)
{
	color_rgb(mlx, 0, 0, mlx->ui.rgbcircle);
	mlx->ui.cube_cam = mlx->cam;
	mlx->ui.cube_cam.zoom = 5;
	if (mlx->cam.view)
	{
		img_fill(&mlx->map, &mlx->cam, &mlx->img, mlx->img.x, mlx->img.y, 0);
		img_fill(&mlx->ui.cube_map, &mlx->ui.cube_cam, &mlx->img, 35, 50, 0);
	}
	else
	{
		cam_rayo(mlx, &mlx->map, &mlx->cam, 0);
		img_fill(&mlx->ui.cone_map, &mlx->ui.cube_cam, &mlx->img, 35, 50, 0);
	}
}

void	map_limits(t_map *m)
{
	int	i;

	m->max.x = -999;
	m->min.x = 999;
	m->max.y = -999;
	m->min.y = 999;
	i = 0;
	while (i < m->size)
	{
		if (m->xyzc[i][0] < m->min.x)
			m->min.x = m->xyzc[i][0];
		else if (m->xyzc[i][0] > m->max.x)
			m->max.x = m->xyzc[i][0];
		if (m->xyzc[i][1] < m->min.y)
			m->min.y = m->xyzc[i][1];
		else if (m->xyzc[i][1] > m->max.y)
			m->max.y = m->xyzc[i][1];
		i++;
	}
	//printf("xmax:%f xmin:%f\n", m->max.x, m->min.x);
	//printf("ymax:%f ymin:%f\n", m->max.y, m->min.y);
	//printf("H:%d W:%d\n", m->width, m->height);
}

void	img_fill(t_map *m, t_cam *cam, t_img *img, int gapx, int gapy, int trgb)
{
	int		i;
	t_point	a;
	t_point	b;
	
	map_limits(m);
	i = 0;
	while (i < m->size)
	{
		b = point_move(m, i, -(m->max.x - m->min.x) / 2, -(m->max.y - m->min.y) / 2, 0);
		b = point_project(cam, b, gapx, gapy);
		//if (i > 0 && m->xyzc[i][0] == m->xyzc[i - 1][0])
		if (i > 0 && (i % (m->height + 1)))
			line (img, a, b, trgb * abs(m->xyzc[i][3]));
		a.x = b.x;
		a.y = b.y;
		if (i + m->height + 1 < m->size)
		{
			b = point_move(m, i + m->height + 1, -(m->max.x - m->min.x) / 2, -(m->max.y - m->min.y) / 2, 0);
			b = point_project(cam, b, gapx, gapy);
			line(img, a, b, trgb * abs(m->xyzc[i][3])); 
		}
		i++;
	}
}
