/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:30:59 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/17 15:24:09 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Calculates points in polar coordinates adding radius at certain points
void	sphere_fill(float *point, t_point angle, double z, int r)
{
	int	rad;

	rad = r + z;
	point[0] = (rad * sin(angle.x) * cos(angle.z)); /* +rad */
	point[1] = (rad * cos(angle.x) * cos(angle.z)); /* +rad */
	point[2] = (rad * sin(angle.z));
	point[3] = 0xFFFFFF;
}

//Transform 'z' coordinates from a grid to an array
float	*mapz_to_displacement(t_map map, float scale)
{
	float	*displacement;
	int		i;
	float	dz;

	dz = scale;
	if (dz <= 0.1)
		dz = 0.1;
	else if (dz >= 10)
		dz = 10;
	displacement = malloc(sizeof(float) * map.size);
	i = -1;
	while (++i < map.size)
		displacement[i] = map.xyzc[i][2] * dz;
	return (displacement);
}

void	map_normals(t_map *m)
{
	//int	i;

	//i = -1;
	(void)m;
	/*m->n = malloc(sizeof(t_point) * m->size);
	while (++i < m->size)
	{
		m->n[i] = point_fill(m->xyzc[i][0], m->xyzc[i][1], m->xyzc[i][2]);
		// printf("x: %f y: %f z: %f\n", m->n[i].x, m->n[i].y, m->n[i].z);
		normalize(&m->n[i]);
	}*/
}

//Create a sphere mesh with radius 'r' using height, width and size given
//in map structure, then displace it using a displacement map,
//if dp = NULL displacement will be set to zero
void	sphere_create(t_map *grid, int r, float *dp)
{
	int		i;
	t_point	steps;
	t_point	angle;

	steps.x = 2 * M_PI / (grid->height - 1);
	steps.z = -1 * M_PI / (grid->width);
	angle.x = 0;
	angle.z = M_PI_2;
	i = 0;
	while (i < grid->size)
	{
		if (dp)
			sphere_fill(grid->xyzc[i], angle, dp[i], r);
		else
			sphere_fill(grid->xyzc[i], angle, 0, r);
		angle.x += steps.x;
		if (i > 0 && !(i % (grid->height + 1)))
		{
			angle.x = 0;
			angle.z += steps.z;
		}
		i++;
	}
	if (dp)
		nbr_be_free(dp);
	map_normals(grid);
	// printf("\n\n\n");
}

// Transform a mesh into another
void	metamorphose(t_mlx *mlx, float **ini, float **fin, int point)
{
	fin[point][0] = fin[point][0] * (1 - mlx->ui.a_frame)
		+ ini[point][0] * mlx->ui.a_frame;
	fin[point][1] = fin[point][1] * (1 - mlx->ui.a_frame)
		+ ini[point][1] * mlx->ui.a_frame;
	fin[point][2] = fin[point][2] * (1 - mlx->ui.a_frame)
		+ ini[point][2] * mlx->ui.a_frame;
}

// Old function to transform an sphere to the map
void	sphere_transform(t_mlx *mlx)
{
	float	**sphere;
	int		i;

	sphere = NULL;
	img_clean(mlx);
	if (mlx->ui.a_frame > 0.4)
	{
		mlx->ui.animation = 0;
		mlx->cam.auto_rot[2] = 0;
		map_scale(&mlx->map, 0.1);
		mlx->cam.zoom *= 10;
	}
	else
	{
		if (mlx->ui.time > 25000)
			mlx->ui.a_frame += 0.01;
		sphere = mlx->sphere.xyzc;
		map_limits(&mlx->sphere);
		mlx->cam.zoom = 1 + 420
			/ (1 + fabs(mlx->sphere.max.x - mlx->sphere.min.x));
		i = 0;
		while (i < mlx->map.size && mlx->ui.time > 0)
			metamorphose(mlx, mlx->map.xyzc, sphere, i++);
	}
}
