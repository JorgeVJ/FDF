/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcono.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:18:36 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/30 19:43:38 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	cam_pos(t_cam *cam)
{
	t_point	p;

	p.x = cam->dist * cos(cam->anglev) * sin(cam->angleh);
	p.y = cam->dist * cos(cam->anglev) * cos(cam->angleh);
	p.z = cam->dist * sin(cam->anglev);
	return (p);
}

t_point	intersect(t_map *map, t_cam *cam, int point)
{
	t_point	v;
	t_point	b;
	t_point	p;
	t_point	a;
	double	t;

	b = cam->pos;
	a = point_move(map, point, point_fill(-(map->max.x - map->min.x) / 2,
				-(map->max.y - map->min.y) / 2,
				-(map->max.z - map->min.z) / 2));
	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	t = -(b.x * b.x + b.y * b.y + b.z * b.z)
		/ (b.x * (a.x - b.x) + b.y
			* (a.y - b.y) + b.z * (a.z - b.z));
	p.x = b.x + t * v.x;
	p.y = b.y + t * v.y;
	p.z = b.z + t * v.z;
	return (p);
}

void	proy_conic(t_mlx *mlx, t_map *map, t_cam *cam, int trgb)
{
	t_point	ini;
	t_point	fin;
	t_point	p;
	int		i;

	map_limits(map);
	cam->pos = cam_pos(cam);
	i = 0;
	while (i < map->size)
	{
		p = intersect(map, cam, i);
		fin = point_project(cam, p, mlx->map.gap.x, mlx->map.gap.y);
		if (i > 0 && (i % (map->height + 1)))
			line (&mlx->img, ini, fin,
				trgb * fmax(map->xyzc[i][3], map->xyzc[i - 1][3]));
		ini = fin;
		if (i + map->height + 1 < map->size)
		{
			p = intersect(map, cam, i + map->height + 1);
			fin = point_project(cam, p, mlx->map.gap.x, mlx->map.gap.y);
			line(&mlx->img, ini, fin, trgb * fmax(map->xyzc[i][3],
					map->xyzc[i + map->height + 1][3]));
		}
		i++;
	}
}

int	point_overlap(t_point a, t_point b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (1);
	return (0);
}

t_point	point_fill(int x, int y, int z)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}
