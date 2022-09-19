/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_hooks_outils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:56:13 by jvasquez          #+#    #+#             */
/*   Updated: 2022/09/02 12:16:00 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	auto_rotate(t_mlx *mlx, int key)
{
	if (key == 2)
		mlx->cam.auto_rot[0] = !mlx->cam.auto_rot[0];
	else if (key == 1)
		mlx->cam.auto_rot[2] = !mlx->cam.auto_rot[2];
	else if (key == 0)
		mlx->cam.auto_rot[1] = !mlx->cam.auto_rot[1];
	else if (key == 13)
		mlx->cam.auto_rot[3] = !mlx->cam.auto_rot[3];
}

void	rotate_cam(t_mlx *mlx, int x, int y)
{
	img_clean(mlx);
	mlx->cam.angleh = mlx->cam.angleh + 0.01 * (mlx->mouse.x - x);
	mlx->cam.anglev = mlx->cam.anglev - 0.01 * (mlx->mouse.y - y);
	mlx->mouse.x = x;
	mlx->mouse.y = y;
	img_draw(mlx);
}

void	move_map(t_mlx *mlx, int x, int y)
{
	img_clean(mlx);
	mlx->map.gap.x = mlx->map.gap.x + WIN_W / 2 + x - mlx->mouse.x;
	mlx->map.gap.y = mlx->map.gap.y + WIN_H / 2 + y - mlx->mouse.y;
	mlx->mouse.x = WIN_W / 2 + x;
	mlx->mouse.y = WIN_H / 2 + y;
	img_draw(mlx);
}

void	scale_z(t_mlx *mlx, int x, int y)
{		
	(void)x;
	img_clean(mlx);
	mlx->cam.zscale = mlx->cam.zscale + 0.01 * (mlx->mouse.y - y);
	mlx->mouse.y = y;
	img_draw(mlx);
}
