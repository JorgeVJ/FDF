/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:20:05 by jvasquez          #+#    #+#             */
/*   Updated: 2022/11/16 11:50:06 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/fdf.h"

int	hook_keydown(int key, t_mlx *mlx)
{
	img_clean(mlx);
	if (key >= NPD_1 && key <= NPD_9)
		proyections(mlx, key);
	else if (key == KEY_ESC)
	{
		free(mlx->map.xyzc);
		exit(EXIT_SUCCESS);
	}
	else if ((key >= KEY_A && key <= KEY_D) || key == KEY_W)
		auto_rotate(mlx, key);
	else if (key == KEY_Q)
		mlx->cam.view = !mlx->cam.view;
	else if (key == KEY_C)
		update_value_up(mlx, (double *)(&mlx->cam.dist), 5, INT_MAX);
	else if (key == KEY_V)
		update_value_down(mlx, (double *)(&mlx->cam.dist), -5, 10);
	else if (key == KEY_Z)
		mlx->cam.z_key = !mlx->cam.z_key;
	img_draw(mlx);
	return (0);
}

int	hook_mousemove(int x, int y, t_mlx *mlx)
{
	if (x > WIN_W - 60 && x < WIN_W && y > WIN_H - 60 && y < WIN_H)
		mlx->ui.mouse_in = 1;
	else if (mlx->ui.mouse_in)
		update_value_up(mlx, (double *)(&mlx->ui.mouse_in), 42, 1);
	if (mlx->mouse.l && x < WIN_W && y < WIN_H && x > 0 && y > 0)
		move_map(mlx, x, y);
	else if (mlx->mouse.r && x < WIN_W && y < WIN_H && x > 0 && y > 0)
		rotate_cam(mlx, x, y);
	else if (mlx->cam.z_key)
		scale_z(mlx, x, y);
	return (0);
}

int	hook_mousedown(int button, int x, int y, t_mlx *mlx)
{
	if (button == M_WUP)
		update_value_up(mlx, &mlx->cam.zoom, 1, INT_MAX);
	else if (button == M_WDO && mlx->cam.zoom - 2 > 0)
		update_value_down(mlx, &mlx->cam.zoom, -1, 0);
	if (button == M_LEFT)
		mouse_left(mlx, x, y);
	else if (button == M_RIGHT)
	{
		mlx->mouse.r = 1;
		mlx->mouse.y = y;
	}
		mlx->mouse.x = WIN_W / 2 + x;
	return (0);
}

int	hook_mouseup(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (button == M_LEFT)
		update_value_up(mlx, (double *)(&mlx->mouse.l), 1, 1);
	else if (button == M_RIGHT)
		mlx->mouse.r = 0;
	return (0);
}

int	hook_rotate(t_mlx *mlx)
{
	mlx->ui.time++;
	if (!(mlx->ui.time % 1000) && mlx->ui.animation)
		sphere_transform(mlx);
	if (!(mlx->ui.time % 630) && mlx->ui.mouse_in)
	{
		image_animate(mlx, &mlx->ui.logo, WIN_W - 60, WIN_H - 60);
		key_help(mlx);
		rotations_off(mlx);
	}
	if (!(mlx->ui.time % 420) && mlx->cam.auto_rot[0])
		update_value_up(mlx, &mlx->cam.angleh, 0.02, 2 * M_PI);
	if (!(mlx->ui.time % 420) && mlx->cam.auto_rot[2])
		update_value_up(mlx, &mlx->cam.anglev, 0.02, 2 * M_PI);
	if (!(mlx->ui.time % 420) && mlx->cam.auto_rot[1])
		update_value_down(mlx, &mlx->cam.angleh, -0.02, 2 * M_PI);
	if (!(mlx->ui.time % 420) && mlx->cam.auto_rot[3])
		update_value_down(mlx, &mlx->cam.anglev, -0.02, 2 * M_PI);
	if (mlx->ui.time >= INT_MAX - 1)
		mlx->ui.time = 0;
	return (0);
}
