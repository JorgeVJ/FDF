/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:18:52 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/19 17:41:31 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_split(t_map *map, char **cotas)
{
	char	**datos;

	datos = ft_split(cotas[map->height], ',');
	map->xyzc[0][map->size] = map->width;
	map->xyzc[1][map->size] = map->height;
	map->xyzc[2][map->size] = ft_atoi(datos[0]);
	if (datos[1])
		map->xyzc[3][map->size] = atoi_hexa(datos[1]);
	else
		map->xyzc[3][map->size] = map->colormin;
	free (datos);
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
		free (cotas);
		free (line);
		line = get_next_line(file);
	}
	close(file);
	map->height--;
	map->width--;
}

int	atoi_hexa(char *str)
{
	int	sum;

	sum = 0;
	while (*str == '0' || *str == 'x')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			sum = sum * 16 + *str - '0';
		else if (*str >= 'A' && *str <= 'F')
			sum = sum * 16 + *str - 'A' + 10;
		else if (*str >= 'a' && *str <= 'f')
			sum = sum * 16 + *str - 'a' + 10;
		str++;
	}
	return (sum);
}
