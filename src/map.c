/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:18:52 by jvasquez          #+#    #+#             */
/*   Updated: 2022/11/16 11:43:09 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	chrcount(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == ' ')
			count++;
	}
	return (count);
}

// Open a map file and read it to get dimentions of the map.
void	map_load_dim(char *dir, int *width, int *height)
{
	int		file;
	char	*line;
	int		check;

	*width = 0;
	check = 0;
	file = open(dir, O_RDONLY);
	line = get_next_line(file);
	while (line)
	{
		if (!check)
		{
			*height = chrcount(line);
			check = 1;
		}
		str_be_free(line);
		line = get_next_line(file);
		*width += 1;
	}
	*width -= 1;
	close(file);
	map_error(*height, *width);
}

void	map_fill_from_file(t_map *map, char *dir)
{
	int		file;
	char	*line;
	int		pos;
	t_point	p;
	int		point;

	point = 0;
	file = open(dir, O_RDONLY);
	line = get_next_line(file);
	p.x = 0;
	while (line)
	{
		pos = 0;
		p.y = 0;
		while (line[pos])
		{
			point_create(map, point,
				point_fill(p.x - map->width / 2 , p.y++ - map->height / 2, ft_atoi_pos(line, &pos)));
			map->xyzc[point++][3] = color_read(line, &pos);
		}
		p.x++;
		str_be_free(line);
		line = get_next_line(file);
	}
	close(file);
}

void	map_scale(t_map *m, float scale)
{
	int		point;

	point = -1;
	while (++point < m->size)
	{
		m->xyzc[point][0] = (int)((float)m->xyzc[point][0] * scale);
		m->xyzc[point][1] = (int)((float)m->xyzc[point][1] * scale);
		m->xyzc[point][2] = (int)((float)m->xyzc[point][2] * scale);
	}
}

void	map_limits(t_map *m)
{
	int	i;

	m->max.x = INT_MIN;
	m->min.x = INT_MAX;
	m->max.y = INT_MIN;
	m->min.y = INT_MAX;
	m->max.z = INT_MIN;
	m->min.z = INT_MAX;
	i = 0;
	while (i < m->size)
	{
		if (m->xyzc[i][0] < m->min.x)
			m->min.x = m->xyzc[i][0];
		else if (m->xyzc[i][0] > m->max.x)
			m->max.x = m->xyzc[i][0];
		if (m->xyzc[i][1] < m->min.y)
			m->min.y = m->xyzc[i][1];
		else if (m->xyzc[i][1] > m->max.y)
			m->max.y = m->xyzc[i][1];
		if (m->xyzc[i][2] < m->min.z)
			m->min.z = m->xyzc[i][2];
		else if (m->xyzc[i][2] > m->max.z)
			m->max.z = m->xyzc[i][2];
		i++;
	}
}
