/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:39:15 by jvasquez          #+#    #+#             */
/*   Updated: 2022/11/21 21:47:16 by jvasquez         ###   ########.fr       */
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
		if (max < map->xyzc[i][2])
			max = map->xyzc[i][2];
		else
			min = map->xyzc[i][2];
		if (map->colormax < map->xyzc[i][3])
			map->colormax = map->xyzc[i][3];
		else
			map->colormin = map->xyzc[i][3];
	}	
	if (!(max - min))
		return (1);
	return (max - min);
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
		if (map->colormin == map->xyzc[i][3])
		{
			if (map->colormin < map->colormax)
				map->xyzc[i][3] = trgb(0,
						map->cmin[0] + abs(map->xyzc[i][2]) * step[0],
						map->cmin[1] + abs(map->xyzc[i][2]) * step[1],
						map->cmin[2] + abs(map->xyzc[i][2]) * step[2]);
			else
				map->xyzc[i][3] = trgb(0,
						map->cmax[0] + abs(map->xyzc[i][2]) * step[0],
						map->cmax[1] + abs(map->xyzc[i][2]) * step[1],
						map->cmax[2] + abs(map->xyzc[i][2]) * step[2]);
		}
	}
}

void	map_repaint(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->size)
		map->xyzc[i][3] = map->colormin;
	map_color(map);
}

int	color_read(char *line, int *pos)
{
	int	color;

	color = 0xFF;
	if (line[*pos] == ',')
	{
		*pos += 1;
		color = atoi_hexa_pos(line, pos);
	}
	str_error(line, *pos);
	if (line[*pos] == ' ' || line[*pos] == '\n')
		*pos += 1;
	return (color);
}
