/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:06:07 by jvasquez          #+#    #+#             */
/*   Updated: 2022/12/10 18:06:10 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Testing function to avoid painting the entire sphere in polar projection.
int	check_paint(t_map *map, t_cam *cam, int point, t_point b)
{
	int		angle;
	int		angleh;
	float	m;
	int		r;
	t_point	p;
	t_point n;
	float	sca;

		return (1);
	if (map->id != 1)
		return (1);
	(void)b;
	if (point + map->height + 1 > map->size)
		return (1);
	n = normal(triangle(map, cam, point));
	// normalize(&n);
	cam->pos = cam_pos(cam);
	// normalize(&cam->pos);
	sca = scalar(n, cam->pos, 10, -10);
	if (sca <= 0)
		return (0);
	// printf("scalar %d: %f\n", point, sca);
	// printf("point: %d x: %f y: %f z: %f\n",	point, n.x, n.y, n.z);
	// printf("campo: %f x: %f y: %f z: %f\n",	cam->dist, cam->pos.x, cam->pos.y, cam->pos.z);
	return (1);
	angle = (int)(cam->anglev * 360 / (2 * M_PI)) % 360;
	angleh = (int)(cam->angleh * 360 / (2 * M_PI)) % 360;
	r = map->max.z;
	m = (float)r / 90;
	p.z = map->xyzc[point][2];
	if (angle <= 90 && p.z < m * angle - r)
		return (0);
	else if (angle > 90 && angle <= 180 && p.z < -m * angle + r)
		return (0);
	else if (angle > 180 && angle <= 270 && p.z > -m * (angle - 180) + r)
		return (0);
	else if (angle > 270 && angle <= 360 && p.z > m * (angle - 180) - r)
		return (0);
	return (1);
}
