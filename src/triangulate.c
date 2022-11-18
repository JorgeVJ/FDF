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

t_trian	triangle(t_mlx *mlx, int i)
{
	t_trian	t;

	t.a = get_projected(&mlx->map, &mlx->cam, i);
	t.b = get_projected(&mlx->map, &mlx->cam, i + 1);
	t.c = get_projected(&mlx->map, &mlx->cam, i + mlx->map.height + 1);
	return (t);
}

t_point	get_projected(t_map *m, t_cam *cam, int point)
{
	t_point	a;

	map_limits(m);
	a = point_move(m, point, point_fill(-(m->max.x - m->min.x) / 2,
				-(m->max.y - m->min.y) / 2, 0));
	a = point_project(cam, a, m->gap.x, m->gap.y);
	return (a);
}

void	fill_face(t_mlx *mlx, t_trian t)
{
	line (&mlx->img, t.a, t.b, 0xFFFFFF);
	line (&mlx->img, t.b, t.c, 0xFFFFFF);
	line (&mlx->img, t.a, t.c, 0xFFFFFF);
}
