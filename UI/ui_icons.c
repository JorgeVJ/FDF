/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_icons.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 23:59:32 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/17 15:28:20 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/fdf.h"

void	cube_create(t_map *grid, int a)
{
	int		i;
	int		j;
	int		point;
	float	**cube;

	cube = grid->xyzc;
	j = -1;
	point = 0;
	while (++j < 2)
	{
		i = -1;
		while (++i < 5)
		{
			cube[point][0] = j * a - a / 2;
			cube[point][1] = !((i - 2) & (i - 3)) * a - a / 2;
			cube[point][2] = !((i - 1) & (i - 2)) * a - a / 2;
			cube[point][3] = 0xFFFFFF;
			point++;
		}
	}
}

// Creates a Cone with height = h and base radius = r, filling a grid given.
void	cone_create(t_map *grid, int h, int r)
{
	int		i;
	int		j;
	int		point;
	float	**cone;

	cone = grid->xyzc;
	j = -1;
	point = 0;
	while (++j <= grid->width)
	{
		i = -1;
		while (++i <= grid->height)
		{
			cone[point][0] = (grid->width - j) * (sin(i * 2 * M_PI
						/ grid->height) * r) / grid->width;
			cone[point][1] = (grid->width - j) * (cos(i * 2 * M_PI
						/ grid->height) * r) / grid->width;
			cone[point][2] = h * j / grid->width;
			cone[point][3] = 0xFFFFFF;
			point++;
		}
	}
}

// Reserve memory for a point and fills it with data given.
float	*point_dim(t_point p)
{
	float	*point;

	point = malloc(sizeof(float) * 4);
	point[0] = p.x;
	point[1] = p.y;
	point[2] = p.z;
	return (point);
}

// Initialize a map structure and reserves memory
// according to width and height given as parameters.
t_map	grid_create(int width, int height)
{
	t_map	grid;
	int		point;

	grid.id = 0;
	grid.scale = 1;
	grid.size = (width + 1) * (height + 1);
	grid.width = width;
	grid.height = height;
	grid.colormin = 0xFF;
	grid.colormax = 0xFFFFFF;
	grid.gap.x = UI_X;
	grid.gap.y = UI_Y;
	grid.xyzc = malloc(sizeof(float *) * grid.size);
	point = -1;
	while (++point < grid.size)
		grid.xyzc[point] = point_dim(point_fill(0, 0, 0));
	return (grid);
}
