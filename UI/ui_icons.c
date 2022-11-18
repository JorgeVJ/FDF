/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_icons.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 23:59:32 by jvasquez          #+#    #+#             */
/*   Updated: 2022/09/02 09:52:22 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/fdf.h"

void	cube_create(t_mlx *mlx)
{
	int	i;
	int	j;
	int	point;
	int	**cube;

	cube = malloc(sizeof(int *) * 10);
	j = -1;
	point = 0;
	while (++j < 2)
	{
		i = -1;
		while (++i < 5)
		{
			cube[point] = malloc(sizeof(int) * 4);
			cube[point][0] = j * 40;
			cube[point][1] = !((i - 2) * (i - 3)) * 40;
			cube[point][2] = !((i - 1) * (i - 2)) * 40;
			cube[point][3] = 0xFFFFFF;
			point++;
		}
	}
	mlx->ui.cube_map.xyzc = cube;
}

void	cone_create(t_mlx *mlx)
{
	int	i;
	int	j;
	int	point;
	int	**cone;

	cone = malloc(sizeof(int *) * 18);
	j = -1;
	point = 0;
	while (++j < 2)
	{
		i = -1;
		while (++i < 9)
		{
			cone[point] = malloc(sizeof(int) * 4);
			cone[point][0] = !(j) * (sin(i * M_PI_4) * 20) + 20;
			cone[point][1] = !(j) * (cos(i * M_PI_4) * 20) + 20;
			cone[point][2] = 40 * j;
			cone[point][3] = 0xFFFFFF;
			point++;
		}
	}
	mlx->ui.cone_map.xyzc = cone;
}
