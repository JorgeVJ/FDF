/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:57:14 by jvasquez          #+#    #+#             */
/*   Updated: 2022/09/19 16:29:03 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_ui_maps_init(t_mlx *mlx)
{
	mlx->ui.cube_map.dir = NULL;
	mlx->ui.cube_map.width = 1;
	mlx->ui.cube_map.height = 4;
	mlx->ui.cube_map.size = 10;
	mlx->ui.cube_map.colormin = 0xFFFFFF;
	mlx->ui.cube_map.colormax = 0xFFFFFF;
	mlx->ui.cube_map.gap.x = UI_X;
	mlx->ui.cube_map.gap.y = UI_Y;
	mlx->ui.cube_map.xyzc = NULL;
	mlx->ui.cone_map = mlx->ui.cube_map;
	mlx->ui.cone_map.width = 1;
	mlx->ui.cone_map.height = 8;
	mlx->ui.cone_map.size = 18;
	cube_create(mlx);
	cone_create(mlx);
	map_limits(&mlx->ui.cube_map);
	map_limits(&mlx->ui.cone_map);
}

void	fdf_interface_init(t_mlx *mlx)
{
	fdf_ui_maps_init(mlx);
	mlx->ui.animation = 0;
	mlx->mouse.l = 0;
	mlx->mouse.r = 0;
	mlx->ui.time = 0;
	mlx->ui.mouse_in = 0;
	mlx->ui.rgbcircle = 0;
	mlx->ui.sphere_map.gap.x = WIN_W / 2;
	mlx->ui.sphere_map.gap.y = WIN_H / 2;
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
	mlx->cam.zoom = 1 + 420 / (1 + fabs(mlx->map.max.x - mlx->map.min.x));
	mlx->cam.auto_rot[0] = 1;
	mlx->cam.auto_rot[1] = 0;
	mlx->cam.auto_rot[2] = 0;
	mlx->cam.auto_rot[3] = 0;
	mlx->cam.angleh = 0 * M_PI_4;
	mlx->cam.anglev = 1 * M_PI_4;
	mlx->cam.zscale = 1;
	mlx->cam.z_key = 0;
	mlx->cam.view = 1;
	mlx->cam.dist = 300;
	mlx->ui.cam = mlx->cam;
}

void	fdf_init(t_mlx *mlx, char *dir)
{
	mlx->map.scale = 10;
	mlx->map.xyzc = NULL;
	mlx->map.dir = dir;
	mlx->map.colormin = 0xFF;
	mlx->map.colormax = 0xFFFFFF;
	mlx->map.size = 0;
	mlx->map.width = 0;
	map_fill(&mlx->map, dir);
	map_limits(&mlx->map);
	fdf_cam_init(mlx);
	sphere_create(mlx);
	fdf_interface_init(mlx);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "FDF");
	img_new(mlx);
	map_color(&mlx->map);
	img_draw(mlx);
	mlx->ui.logo.frame = 0;
	image_animate(mlx, &mlx->ui.logo, WIN_W - 60, WIN_H - 60);
}
