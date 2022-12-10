/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:57:14 by jvasquez          #+#    #+#             */
/*   Updated: 2022/11/22 11:57:28 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_ui_maps_init(t_mlx *mlx)
{
	mlx->ui.cube_map = grid_create(1, 4);
	cube_create(&mlx->ui.cube_map, 40);
	mlx->ui.cone_map = grid_create(6, 6);
	cone_create(&mlx->ui.cone_map, 40, 20);
	mlx->ui.sphere_map = grid_create(8, 8);
	sphere_create(&mlx->ui.sphere_map, 30, NULL);
	map_repaint(&mlx->ui.sphere_map);
}

void	fdf_interface_init(t_mlx *mlx)
{
	mlx->p = 0;
	fdf_ui_maps_init(mlx);
	mlx->ui.animation = 0;
	ft_bzero(&mlx->mouse, sizeof(t_mouse));
	mlx->ui.time = 0;
	mlx->ui.mouse_in = 0;
	mlx->ui.rgbcircle = 0;
	mlx->sphere.id = 2;
	mlx->sphere.gap.x = WIN_W / 2;
	mlx->sphere.gap.y = WIN_H / 2;
	mlx->map.gap.x = WIN_W / 2;
	mlx->map.gap.y = WIN_H / 2;
	mlx->ui.a_frame = 0;
	mlx->ui.x = 25;
	mlx->ui.y = WIN_H - 25;
	images_load(mlx, &mlx->ui.keys, "UI/Keys/00.xpm", 4);
	images_load(mlx, &mlx->ui.logo, "UI/Button/00.xpm", 30);
}

void	fdf_cam_init(t_mlx *mlx)
{
	ft_bzero(&mlx->cam, sizeof(t_cam));
	mlx->cam.zoom = 1 + 420 / (1 + fabs(mlx->map.max.x - mlx->map.min.x));
	mlx->cam.angleh = 1 * M_PI_4 * 0;
	mlx->cam.anglev = 3 * M_PI_4 * 0;
	mlx->cam.zscale = 1;
	mlx->cam.view = 1;
	mlx->cam.dist = 300;
	mlx->ui.cam = mlx->cam;
}

// Initialize an array of integers to save the position of pixels painted
// usefull for small maps with no repainted pixels.
/*void	*cleaner_init(t_mlx *mlx)
{
	long int	size;
	int			*clean;

	size = WIN_H * WIN_W;
	clean = malloc(sizeof(int) * size);
	if (!clean)
		return (NULL);
	mlx->cleaner = clean;
	return (clean);
}*/

// Does this really needs an explanation?
// Take color value from one map and transfer it to another one
void	copy_colors_from_map(t_map *dst, t_map src)
{
	int	point;
	int	size;

	if (dst->size > src.size)
		size = src.size;
	else
		size = dst->size;
	point = -1;
	while (++point < size)
		dst->xyzc[point][3] = src.xyzc[point][3];
}

// Just testing things...
/*void	wave(t_mlx *mlx)
{
	int	i;
	t_point p;
	float k;
	float f;

	printf("%d\n", mlx->ui.time);
	i = -1;
	while (++i < mlx->map.size)
	{
		// p.x = mlx->map.xyzc[i][0];
		// p.y = mlx->map.xyzc[i][1];
		k = 2 * M_PI / 100;
		f = k * (p.x + mlx->ui.time / 500);
		mlx->map.xyzc[i][0] += 2 * cos(f);
		mlx->map.xyzc[i][1] += 2 * sin(f);
		mlx->map.xyzc[i][2] = p.x + p.y;
	}
}*/

// mlx->cleaner = cleaner_init(mlx);
// Cleaner must be initialized before img_new for some strange reason.
void	fdf_init(t_mlx *mlx, char *dir)
{
	ft_bzero(&mlx->map, sizeof(t_map));
	map_load_dim(dir, &mlx->map.width, &mlx->map.height);
	mlx->map = grid_create(mlx->map.width, mlx->map.height);
	mlx->map.scale = 10;
	map_fill_from_file(&mlx->map, dir);
	map_limits(&mlx->map);
	remaping(&mlx->map, 0, 42);
	fdf_cam_init(mlx);
	mlx->sphere = grid_create(mlx->map.width, mlx->map.height);
	sphere_create(&mlx->sphere, 150, mapz_to_displacement(mlx->map, 1));
	copy_colors_from_map(&mlx->sphere, mlx->map);
	fdf_interface_init(mlx);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "FDF");
	img_new(mlx);
	map_color(&mlx->map);
	img_draw(mlx);
	mlx->ui.logo.frame = 0;
	image_animate(mlx, &mlx->ui.logo, WIN_W - 60, WIN_H - 60);
}
