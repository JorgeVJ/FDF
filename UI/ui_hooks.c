/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:20:05 by jvasquez          #+#    #+#             */
/*   Updated: 2022/11/25 22:00:23 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/fdf.h"

int	hook_keydown(int key, t_mlx *mlx)
{
	img_clean(mlx);
	mlx->mouse.x = mlx->mouse.posx;
	mlx->mouse.y = mlx->mouse.posy;
	if (key >= NPD_1 && key <= NPD_9)
		proyections(mlx, key);
	else if (key == KEY_ESC)
		exit(EXIT_SUCCESS);
	else if ((key >= KEY_A && key <= KEY_D) || key == KEY_W)
		auto_rotate(mlx, key);
	else if (key == KEY_Q)
		update_int_up(mlx, &mlx->cam.view, 1, 3);
	else if (key == KEY_C)
		update_value_up(mlx, (double *)(&mlx->cam.dist), 5, INT_MAX);
	else if (key == KEY_V)
		update_value_down(mlx, (double *)(&mlx->cam.dist), -5, 10);
	else if (key == KEY_Z)
		mlx->cam.z_key = !mlx->cam.z_key;
	else if (key == KEY_E)
		mlx->ui.menu_in = !mlx->ui.menu_in;
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
	else if (mlx->ui.menu_in)
		menu_hover(mlx, &mlx->ui.menu, x, y);
	mlx->mouse.posx = x;
	mlx->mouse.posy = y;
	return (0);
}

int	hook_mousedown(int button, int x, int y, t_mlx *mlx)
{
	mlx->mouse.x = mlx->mouse.posx;
	mlx->mouse.y = mlx->mouse.posy;
	if (button == M_WUP)
		update_value_up(mlx, &mlx->cam.zoom, 0.2, INT_MAX);
	else if (button == M_WDO && mlx->cam.zoom - 0.3 > 0)
		update_value_down(mlx, &mlx->cam.zoom, -0.2, 0);
	if (button == M_LEFT)
		mouse_left(mlx, x, y);
	else if (button == M_RIGHT)
		mlx->mouse.r = 1;
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

// if (!(mlx->ui.time % 1000) && mlx->ui.animation)
	// sphere_transform(mlx);
int	hook_rotate(t_mlx *mlx)
{
	mlx->ui.time++;
	if (!(mlx->ui.time & 4096) && mlx->ui.mouse_in)
	{
		image_animate(mlx, &mlx->ui.logo, WIN_W - 60, WIN_H - 60);
		key_help(mlx);
		rotations_off(mlx);
	}
	if (!(mlx->ui.time & 420) && mlx->cam.auto_rot[0])
		update_value_up(mlx, &mlx->cam.angleh, 0.02, 2 * M_PI);
	if (!(mlx->ui.time & 420) && mlx->cam.auto_rot[2])
		update_value_up(mlx, &mlx->cam.anglev, 0.02, 2 * M_PI);
	if (!(mlx->ui.time & 420) && mlx->cam.auto_rot[1])
		update_value_down(mlx, &mlx->cam.angleh, -0.02, 2 * M_PI);
	if (!(mlx->ui.time & 420) && mlx->cam.auto_rot[3])
		update_value_down(mlx, &mlx->cam.anglev, -0.02, 2 * M_PI);
	if (mlx->ui.time >= INT_MAX - 1)
		mlx->ui.time = 0;
	return (0);
}
