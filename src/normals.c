/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:38:56 by jvasquez          #+#    #+#             */
/*   Updated: 2022/12/11 14:38:57 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Normalize a vector and return module of the vector
float normalize(t_point *v)
{
	float	module;

	module = sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
	v->x /= module;
	v->y /= module;
	v->z /= module;
	return (module);
}

void	normal_generic(t_mlx *m)
{
	t_point	p;
	t_point	v;
	float	size = 600;

	ft_bzero(&v, sizeof(t_point));
	m->n.gen = malloc(sizeof(t_point *) * (size + 1));
	p.x = -1;
	while (++p.x <= size)
	{
		m->n.gen[(int)p.x] = malloc(sizeof(t_point) * (size + 1));
		p.y = -1;
		while (++p.y <= size)
		{
			v.x = (1 + sin(p.x * M_PI / size - M_PI_2)) * 0.5;
			v.y = (1 + -sin(p.y * M_PI / size - M_PI_2)) * 0.5;
			v.z = (1 + cos(p.y * M_PI / size - M_PI_2) * cos(p.x * M_PI / size - M_PI_2)) * 0.5;
			m->n.gen[(int)p.x][(int)p.y] = v;
			// my_mlx_pixel_put(&m->img, p.x + 100, p.y + 100, trgb(0, v.x * 255, v.y * 255, v.z * 255));
		}
	}
}

float	distance(t_point a, t_point b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2)));
}