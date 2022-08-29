/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:18:52 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/29 12:46:36 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	**add_point(int **points, int size, t_point p, int rgb)
{
	int	**temp;
	int		i;
	int		j;

	temp = malloc(sizeof(int *) * size);
	i = 0;
	while (points && i < size - 1)
	{
		temp[i] = malloc(sizeof(int) * 4);
		j = -1;
		while (++j <= 3)
			temp[i][j] = points[i][j];
		i++;
	}
	if (points)
	{
		free(points);
		points = NULL;
	}
	temp[i] = malloc(sizeof(int) * 4);
	temp[i][0] = p.x;
	temp[i][1] = p.y;
	temp[i][2] = p.z;
	temp[i][3] = rgb;
	return (temp);
}

void	map_split(t_map *map, char **cotas)
{
	char	**datos;
	int		len;

	datos = ft_split(cotas[map->height], ',');
	len = datos_len(datos);
	if (len == 1)
		fill_one(map, datos);
	else if (len == 2)
		fill_two(map, datos);
	else if (len == 4)
		fill_four(map, datos);
	if (datos)
	{
		free (datos);
		datos = NULL;
	}	
}

void	map_fill(t_map *map, char *dir)
{
	int		file;
	char	*line;
	char	**cotas;

	file = open(dir, O_RDONLY);
	line = get_next_line(file);
	while (line)
	{
		cotas = ft_split(line, ' ');
		map->height = 0;
		while (cotas[map->height])
		{
			map_split(map, cotas);
			map->size++;
			map->height++;
		}
		map->width++;
		if (cotas)
		{
			free (cotas);
			cotas = NULL;
		}
		if (line)
		{
			free (line);
			line = NULL;
		}
		line = get_next_line(file);
	}
	close(file);
	map->height--;
	map->width--;
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
