/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:39:15 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/19 17:37:56 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	map_deltaz(t_map *map)
{
	int	i;
	int	max;
	int	min;

	max = -999;
	min = 999;
	i = -1;
	while (++i < map->size)
	{
		if (max < map->xyzc[2][i])
			max = map->xyzc[2][i];
		else
			min = map->xyzc[2][i];
		if (map->colormax < map->xyzc[3][i])
			map->colormax = map->xyzc[3][i];
		else
			map->colormin = map->xyzc[3][i];
	}	
	return (max - min);
}

int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	to_rgb(t_map *map, int max, int min)
{
	map->cmax[0] = (max >> 16) & 0xFF;
	map->cmax[1] = (max >> 8) & 0xFF;
	map->cmax[2] = max & 0xFF;
	map->cmin[0] = (min >> 16) & 0xFF;
	map->cmin[1] = (min >> 8) & 0xFF;
	map->cmin[2] = min & 0xFF;
}

void	map_color(t_map *map)
{
	int		i;
	int		step[3];

	to_rgb(map, map->colormax, map->colormin);
	i = -1;
	while (++i <= 2)
			step[i] = (map->cmax[i] - map->cmin[i]) / map_deltaz(map);
	i = -1;
	while (++i < map->size)
	{
		if (map->colormin == map->xyzc[3][i])
		{
			if (map->colormin < map->colormax)
				map->xyzc[3][i] = trgb(0,
						map->cmin[0] + map->xyzc[2][i] * step[0],
						map->cmin[1] + map->xyzc[2][i] * step[1],
						map->cmin[2] + map->xyzc[2][i] * step[2]);
			else
				map->xyzc[3][i] = trgb(0,
						map->cmax[0] + map->xyzc[2][i] * step[0],
						map->cmax[1] + map->xyzc[2][i] * step[1],
						map->cmax[2] + map->xyzc[2][i] * step[2]);
		}
	}
}

void	map_repaint(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->size)
		map->xyzc[3][i] = map->colormin;
	map_color(map);
}
