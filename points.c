/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cambio.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:29:54 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/19 20:43:15 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	point_move(t_map *m, int point, int dx, int dy)
{
	t_point	p;

	p.x = m->xyzc[0][point] + dx;
	p.y = m->xyzc[1][point] + dy;
	p.z = m->xyzc[2][point];
	return (p);
}

t_point	point_project(t_mlx *mlx, t_point a, int gapx, int gapy)
{
	int		d;
	t_point	p;

	d = mlx->cam.zoom;
	p.x = gapx + rotz(mlx, a.x * d, a.y * d, 0);
	p.y = gapy + rotx(mlx, rotz(mlx, a.x * d, a.y * d, 1), a.z);
	return (p);
}

int	rotz(t_mlx *mlx, int x, int y, int xy)
{
	if (xy == 0)
		return (x * cos(mlx->cam.angleh) - y * sin(mlx->cam.angleh));
	else
		return (y * cos(mlx->cam.angleh) + x * sin(mlx->cam.angleh));
}

int	rotx(t_mlx *mlx, int y, int z)
{
	z *= -mlx->cam.zoom;
	return (z * cos(mlx->cam.anglev) + y * sin(mlx->cam.anglev));
}

void	line(t_mlx *mlx, int xpf, int ypf, int trgb)
{
	int	x;
	int	y;

	if (fabs(xpf - mlx->line.xo) > fabs(ypf - mlx->line.yo))
	{
		x = fmin(mlx->line.xo, xpf);
		while (++x < fmax(mlx->line.xo, xpf))
		{
			y = (ypf - mlx->line.yo) * (x - mlx->line.xo) / (xpf - mlx->line.xo)
				+ mlx->line.yo;
			my_mlx_pixel_put(&mlx->img, x, y, trgb);
		}
	}
	else
	{
		y = fmin(mlx->line.yo, ypf);
		while (++y < fmax(mlx->line.yo, ypf))
		{
			x = (xpf - mlx->line.xo) * (y - mlx->line.yo) / (ypf - mlx->line.yo)
				+ mlx->line.xo;
			my_mlx_pixel_put(&mlx->img, x, y, trgb);
		}
	}
}
