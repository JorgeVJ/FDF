/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:10:22 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/19 20:49:16 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_init(t_mlx *mlx, char *dir)
{
	mlx->map.dir = dir;
	mlx->map.colormin = 0xFF;
	mlx->map.colormax = 0xFFFFFF;
	mlx->map.size = 0;
	mlx->map.width = 0;
	mlx->cam.zoom = 21;
	mlx->cam.auto_rot = 0;
	mlx->cam.angleh = 1 * M_PI_4;
	mlx->cam.anglev = 1 * M_PI_4;
	mlx->img.x = WIN_W / 2;
	mlx->img.y = WIN_H / 2;
	mlx->mouse.l = 0;
	mlx->mouse.r = 0;
	mlx->ui.rgbcircle = 0;
	mlx->ui.x = 25;
	mlx->ui.y = WIN_H - 25;
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	fdf_init(&mlx, argv[argc * 0 + 1]);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_W, WIN_H, "FDF");
	map_fill(&mlx.map, mlx.map.dir);
	map_color(&mlx.map);
	img_new(&mlx);
	mlx_hook(mlx.win, 4, 0, hook_mousedown, &mlx);
	mlx_hook(mlx.win, 5, 0, hook_mouseup, &mlx);
	mlx_hook(mlx.win, 6, 0, hook_mousemove, &mlx);
	mlx_key_hook(mlx.win, hook_keydown, &mlx.mlx);
	mlx_loop_hook(mlx.mlx, hook_rotate, &mlx);
	mlx_loop(mlx.mlx);
}
