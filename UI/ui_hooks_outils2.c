/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_hooks_outils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <jvasquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:56:13 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/19 17:16:38 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/fdf.h"

void	auto_rotate(t_mlx *mlx, int key)
{
	if (key == XK_d)
		mlx->cam.auto_rot[0] = !mlx->cam.auto_rot[0];
	else if (key == XK_s)
		mlx->cam.auto_rot[2] = !mlx->cam.auto_rot[2];
	else if (key == XK_a)
		mlx->cam.auto_rot[1] = !mlx->cam.auto_rot[1];
	else if (key == XK_w)
		mlx->cam.auto_rot[3] = !mlx->cam.auto_rot[3];
}

void	rotate_cam(t_mlx *m, int x, int y)
{
	img_clean(m);
	update_value_up(m, &m->cam.anglev, -0.01 * (m->mouse.y - y), 2 * M_PI);
	update_value_up(m, &m->cam.angleh, 0.01 * (m->mouse.x - x), 2 * M_PI);
	m->mouse.x = x;
	m->mouse.y = y;
	img_draw(m);
}

void	move_map(t_mlx *mlx, int x, int y)
{
	img_clean(mlx);
	mlx->map.gap.x = mlx->map.gap.x + x - mlx->mouse.x;
	mlx->map.gap.y = mlx->map.gap.y + y - mlx->mouse.y;
	mlx->mouse.x = x;
	mlx->mouse.y = y;
	img_draw(mlx);
}

void	scale_z(t_mlx *mlx, int x, int y)
{
	static float	scale = 1;

	(void)x;
	img_clean(mlx);
	mlx->cam.zscale = mlx->cam.zscale + 0.01 * (mlx->mouse.y - y);
	scale = scale + 0.01 * (mlx->mouse.y - y);
	if (mlx->cam.view == 2)
	{
		mlx->cam.zscale = 1;
		sphere_create(&mlx->sphere, 150, mapz_to_displacement(mlx->map, scale));
		copy_colors_from_map(&mlx->sphere, mlx->map);
	}
	mlx->mouse.y = y;
	img_draw(mlx);
}

int	hook_exit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->map.xyzc);
	exit(EXIT_SUCCESS);
	return (0);
}
