/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 21:14:17 by jvasquez          #+#    #+#             */
/*   Updated: 2022/09/02 10:43:43 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi_pos(char *str, int *pos)
{
	unsigned long int	sum;
	int					sign;

	sum = 0;
	sign = 1;
	str_error(str, *pos);
	if (str[*pos] == '-' || str[*pos] == '+')
	{
		if (str[*pos] == '-')
			sign *= -1;
		*pos += 1;
	}
	while (str[*pos] >= '0' && str[*pos] <= '9')
	{
		sum = - '0' + sum * 10 + str[*pos];
		*pos += 1;
	}
	return (sign * sum);
}

int	atoi_hexa_pos(char *str, int *pos)
{
	int	sum;

	sum = 0;
	while (str[*pos] == '0' || str[*pos] == 'x')
		*pos += 1;
	while (ft_strchr("0123456789ABCDEFabcdef", str[*pos]))
	{
		if (str[*pos] >= '0' && str[*pos] <= '9')
			sum = sum * 16 + str[*pos] - '0';
		else if (str[*pos] >= 'A' && str[*pos] <= 'F')
			sum = sum * 16 + str[*pos] - 'A' + 10;
		else if (str[*pos] >= 'a' && str[*pos] <= 'f')
			sum = sum * 16 + str[*pos] - 'a' + 10;
		*pos += 1;
	}
	return (sum);
}

void	point_create(t_map *map, int point, t_point p)
{
	map->xyzc[point][0] = p.x * map->scale;
	map->xyzc[point][1] = p.y * map->scale;
	map->xyzc[point][2] = p.z * map->scale;
}

void	remaping(t_map *map, float l_inf, float l_sup)
{
	int	i;

	i = -1;
	map_limits(map);
	while (++i < map->size)
		map->xyzc[i][2] = l_inf + (l_sup - l_inf)
			* ((map->xyzc[i][2] - map->min.z) / (map->max.z - map->min.z));
}

int	map_deltaz(t_map map)
{
	int	i;
	int	max;
	int	min;

	max = INT_MIN;
	min = INT_MAX;
	i = -1;
	while (++i < map.size)
	{
		if (max < map.xyzc[i][2])
			max = map.xyzc[i][2];
		else
			min = map.xyzc[i][2];
	}
	if (!(max - min))
		return (1);
	return (max - min);
}
