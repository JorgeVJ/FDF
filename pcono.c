/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcono.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:18:36 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/25 16:27:17 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	cam_pos(t_cam *cam)
{
	t_point	p;

	p.x = cam->dist * cos(cam->anglev) * sin(cam->angleh);
	p.y = cam->dist * cos(cam->anglev) * cos(cam->angleh);
	p.z = cam->dist * sin(cam->anglev);
			//printf("camp.x:%f p.y:%f p.z:%f\n", p.x, p.y, p.z);

	return (p);
}

t_point	intersect(t_map *map, t_cam *cam, int point)
{
	t_point v;
	t_point	b;
	t_point p;
	t_point	a;
	double	t;

		b = cam->pos;
		a = point_move(map, point, -(map->max.x - map->min.x) / 2, -(map->max.y - map->min.y) / 2, -(map->max.z - map->min.z) / 2);
		v.x = a.x - b.x;
		v.y = a.y - b.y;
		v.z = a.z - b.z;
		t = -(b.x * b.x + b.y * b.y + b.z * b.z) / (b.x * (a.x - b.x) + b.y * (a.y - b.y) + b.z * (a.z - b.z));
		p.x = b.x + t * v.x;
		p.y = b.y + t * v.y;
		p.z = b.z + t * v.z;
		return (p);
}

void	cam_rayo(t_mlx *mlx, t_map *map, t_cam *cam, int trgb)
{
	t_point ini;
	t_point	fin;
	t_point p;
	int	i;

	map_limits(map);
	cam->pos = cam_pos(cam);
	i = 0;
	while (i < map->size)
	{
		//if (i > 0 && i < 5)
		p = intersect(map, cam, i);
			printf("ap.x:%f p.y:%f p.z:%f\n", p.x, p.y, p.z);
		fin = point_project(cam, p, mlx->img.x, mlx->img.y);
		if (i > 0 && (i % (map->height + 1)))
			line (&mlx->img, ini, fin, trgb * map->xyzc[i][3]);
		ini = fin;
		if (i + map->height + 1 < map->size)
		{
			p = intersect(map, cam, i + map->height + 1);
			fin = point_project(cam, p, mlx->img.x, mlx->img.y);
			line (&mlx->img, ini, fin, trgb * map->xyzc[i][3]);	
		}
		i++;
	}
}
//printf("ap.x:%f p.y:%f p.z:%f\n", p.x, p.y, p.z);
//printf("ah:%f av:%f\n\n",  cam->angleh, cam->anglev);
//printf("bp.x:%f p.y:%f p.z:%f\n", p.x, p.y, p.z);
//printf("ah:%f av:%f\n\n",  cam->angleh, cam->anglev);
