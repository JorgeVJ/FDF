/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:10:22 by jvasquez          #+#    #+#             */
/*   Updated: 2022/09/01 22:39:31 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_ui_maps_init(t_mlx *mlx)
{
	mlx->ui.cube_map.dir = "UI/cube";
	mlx->ui.cone_map.dir = "UI/cone";
	mlx->ui.cube_map.gap.x = UI_X;
	mlx->ui.cube_map.gap.y = UI_Y;
	mlx->ui.cone_map.gap.x = UI_X;
	mlx->ui.cone_map.gap.y = UI_Y;
	mlx->ui.cube_map.xyzc = NULL;
	mlx->ui.cube_map.xyzc = NULL;
	mlx->ui.cube_map.xyzc = NULL;
	mlx->ui.cone_map.xyzc = NULL;
	mlx->ui.cube_map.size = 0;
	mlx->ui.cone_map.size = 0;
	mlx->ui.cube_map.scale = 1;
	mlx->ui.cone_map.scale = 1;
	map_fill(&mlx->ui.cube_map, mlx->ui.cube_map.dir);
	map_fill(&mlx->ui.cone_map, mlx->ui.cone_map.dir);
}

//	fdf_ui_maps_init(mlx);
//	mlx->ui.cube_cam.zoom = 5;
//	mlx->ui.cube_cam.dist = 25;
void	fdf_interface_init(t_mlx *mlx)
{
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
	mlx->cam.view = 1;
	mlx->cam.dist = 300;
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
	image_animate(mlx, &mlx->ui.logo, WIN_W - 60, WIN_H - 60);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	fdf_init(&mlx, argv[argc * 0 + 1]);
	mlx_hook(mlx.win, 4, 0, hook_mousedown, &mlx);
	mlx_hook(mlx.win, 5, 0, hook_mouseup, &mlx);
	mlx_hook(mlx.win, 6, 0, hook_mousemove, &mlx);
	mlx_key_hook(mlx.win, hook_keydown, &mlx.mlx);
	mlx_loop_hook(mlx.mlx, hook_rotate, &mlx);
	mlx_loop(mlx.mlx);
}
