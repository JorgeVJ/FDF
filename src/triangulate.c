/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:38:04 by jvasquez          #+#    #+#             */
/*   Updated: 2022/11/16 11:51:24 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	get_projected(t_map *m, t_cam *cam, int point)
{
	t_point	a;

	map_limits(m);
	a = point_move(m, point, point_fill(-(m->max.x - m->min.x) / 2,
				-(m->max.y - m->min.y) / 2, 0));
	a = point_project(cam, a, m->gap.x, m->gap.y);
	return (a);
}

t_point	normal(t_trian p)
{
	t_trian	v;

	v.a = point_fill(p.b.x - p.a.x, p.b.y - p.a.y, p.b.z - p.a.z);
	v.b = point_fill(p.c.x - p.a.x, p.c.y - p.a.y, p.c.z - p.a.z);
	v.c = point_fill(v.a.y * v.b.z - v.a.z * v.b.y,
		-(v.a.x * v.b.z - v.a.z * v.b.x),
		v.a.x * v.b.y - v.a.y * v.b.x);
	return (v.c);
}

t_trian	triangle(t_map *map, t_cam *cam, int i)
{
	t_trian	t;

	t.a = get_projected(map, cam, i);
	t.b = get_projected(map, cam, i + 1);
	t.c = get_projected(map, cam, i + map->height + 1);
	return (t);
}

void	fill_face(t_mlx *mlx, t_trian t)
{
	line (mlx, t.a, t.b, 0xFFFFFF);
	line (mlx, t.b, t.c, 0xFFFFFF);
	line (mlx, t.a, t.c, 0xFFFFFF);
}
