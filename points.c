/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cambio.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:29:54 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/25 18:26:31 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	point_move(t_map *m, int point, int dx, int dy, int dz)
{
	t_point	p;

	p.x = m->xyzc[point][0] + dx;
	p.y = m->xyzc[point][1] + dy;
	p.z = m->xyzc[point][2] + dz;
	return (p);
}

t_point	point_project(t_cam *cam, t_point a, int gapx, int gapy)
{
	int		d;
	t_point	p;

	d = cam->zoom;
	p.x = gapx + rotz(cam, a.x * d, a.y * d, 0);
	p.y = gapy + rotx(cam, rotz(cam, a.x * d, a.y * d, 1), a.z);
	return (p);
}

double	rotz(t_cam *cam, double x, double y, double xy)
{
	if (xy == 0)
		return (x * cos(cam->angleh) - y * sin(cam->angleh));
	else
		return (y * cos(cam->angleh) + x * sin(cam->angleh));
}

double rotx(t_cam *cam, double y, double z)
{
	z *= -cam->zoom;
	return (z * cos(cam->anglev) + y * sin(cam->anglev));
}

void	line(t_img *img, t_point a, t_point b, int trgb)
{
	int	x;
	int	y;

	if (fabs(b.x - a.x) > fabs(b.y - a.y))
	{
		x = fmin(a.x, b.x);
		while (++x < fmax(a.x, b.x))
		{
			y = (b.y - a.y) * (x - a.x) / (b.x - a.x) + a.y;
			my_mlx_pixel_put(img, x, y, trgb);
		}
	}
	else if (fabs(b.x - a.x) <= fabs(b.y - a.y))
	{
		x = fmin(a.y, b.y);
		while (++x < fmax(a.y, b.y))
		{
			y = (b.x - a.x) * (x - a.y) / (b.y - a.y) + a.x;
			my_mlx_pixel_put(img, y, x, trgb);
		}
	}
}
