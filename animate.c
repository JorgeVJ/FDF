/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:30:59 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/26 18:34:12 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	sphere_init(t_mlx *mlx)
{
	mlx->ui.sphere_map.width = mlx->map.width;
	mlx->ui.sphere_map.height = mlx->map.height;
	mlx->ui.sphere_map.size = mlx->map.size;
	mlx->ui.sphere_map.colormin = mlx->map.colormin;
	mlx->ui.sphere_map.colormax = mlx->map.colormax;
	mlx->ui.sphere_map.xyzc = malloc(sizeof(int *) * mlx->map.size);
}

void	sphere_fill(int	**sphere, int point, t_point angle)
{
	sphere[point] = malloc(sizeof(int) * 4);
	sphere[point][0] = (int)(42 * sin(angle.x) * cos(angle.z)) + 20;
	sphere[point][1] = (int)(42 * cos(angle.x) * cos(angle.z)) + 20;
	sphere[point][2] = (int)(42 * sin(angle.z));
	sphere[point][3] = 0xFF;
}

void	create(t_mlx *mlx)
{
	int		i;
	int		**sphere;
	t_point	steps;
	t_point	angle;

	sphere_init(mlx);
	sphere = mlx->ui.sphere_map.xyzc;
	steps.x = 2 * M_PI / (mlx->map.width + 1);
	steps.z = 2 * M_PI / (mlx->map.height + 1);
	angle.x = 0;
	angle.z = -M_PI_2;
	i = 0;
	while (i < mlx->map.size)
	{
		sphere_fill(sphere, i, angle);
		angle.x += steps.x;
		if (i > 0 && !(i % (mlx->map.height + 1)))
		{
			angle.x = 0;
			angle.z += steps.z;
		}
		i++;
	}
}

void	metamorphose(t_mlx *mlx, int **sphere, int point)
{
	sphere[point][0] = sphere[point][0] * (1 - mlx->ui.a_frame)
		+ mlx->map.xyzc[point][0] * mlx->ui.a_frame;
	sphere[point][1] = sphere[point][1] * (1 - mlx->ui.a_frame)
		+ mlx->map.xyzc[point][1] * mlx->ui.a_frame;
	sphere[point][2] = sphere[point][2] * (1 - mlx->ui.a_frame)
		+ mlx->map.xyzc[point][2] * mlx->ui.a_frame;
}

void	sphere_transform(t_mlx *mlx)
{
	int	**sphere;
	int	i;

	sphere = NULL;
	img_clean(mlx);
	if (mlx->ui.a_frame > 0.4)
	{
		mlx->ui.animation = 0;
		mlx->cam.auto_rot[2] = 0;
		if (sphere)
			free(sphere);
		sphere = NULL;
	}
	if (mlx->ui.time > 25000)
		mlx->ui.a_frame += 0.01;
	sphere = mlx->ui.sphere_map.xyzc;
	map_limits(&mlx->ui.sphere_map);
	mlx->cam.zoom = 1 + 420
		/ (1 + fabs(mlx->ui.sphere_map.max.x - mlx->ui.sphere_map.min.x));
	i = 0;
	while (i < mlx->map.size && mlx->ui.time > 0)
	{
		metamorphose(mlx, sphere, i);
		i++;
	}
}
