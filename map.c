/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:18:52 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/25 12:57:56 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	**add_point(int	**points, int	size, int x, int y, int z, int rgb)
{
	int	**temp;
	int	i;
	int	j;
	
	//printf("%d\n",  size);
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
		free(points);
	temp[i] = malloc(sizeof(int) * 4);
	temp[i][0] = x;
	temp[i][1] = y;
	temp[i][2] = z;
	temp[i][3] = rgb;
	return (temp);
}

void	fill_one(t_map *map, char **datos)
{
	map->xyzc = add_point(map->xyzc, map->size + 1, map->width, map->height, ft_atoi(datos[0]), map->colormin);
	/*map->xyzc[map->size][0] = map->width;
	map->xyzc[map->size][1] = map->height;
	map->xyzc[map->size][2] = ft_atoi(datos[0]);
	map->xyzc[map->size][3] = map->colormin;*/
}

void	fill_two(t_map *map, char **datos)
{
	map->xyzc = add_point(map->xyzc, map->size + 1, map->width, map->height, ft_atoi(datos[0]), atoi_hexa(datos[1]));
/*	map->xyzc[map->size][0] = map->width;
	map->xyzc[map->size][1] = map->height;
	map->xyzc[map->size][2] = ft_atoi(datos[0]);
	map->xyzc[map->size][3] = atoi_hexa(datos[1]);*/
}

void	fill_four(t_map *map, char **datos)
{	
	map->xyzc = add_point(map->xyzc, map->size + 1, ft_atoi(datos[0]), ft_atoi(datos[1]), ft_atoi(datos[2]), atoi_hexa(datos[3]));
//	map->xyzc[map->size][0] = ft_atoi(datos[0]);
//	map->xyzc[map->size][1] = ft_atoi(datos[1]);
//	map->xyzc[map->size][2] = ft_atoi(datos[2]);
//	map->xyzc[map->size][3] = atoi_hexa(datos[3]);

}

int	datos_len(char **datos)
{
	int	i;

	i = 0;
	while (datos[i])
		i++;
	return (i);
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
