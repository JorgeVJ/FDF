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
int	check_paint(t_map *map, t_cam *cam, int point)
{
	int		angle;
	int		angleh;
	float	m;
	int		r;
	t_point	p;

	if (map->id != 2)
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
