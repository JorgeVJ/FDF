/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:20:05 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/30 12:26:07 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hook_keydown(int key, t_mlx *mlx)
{
	img_clean(mlx);
	if (key >= 83 && key <= 93)
		proyections(mlx, key);
	else if (key == 53)
	{
		free(mlx->map.xyzc);
		exit(EXIT_SUCCESS);
	}
	else if (key == 2)
		mlx->cam.auto_rot[0] = !mlx->cam.auto_rot[0];
	else if (key == 1)
		mlx->cam.auto_rot[2] = !mlx->cam.auto_rot[2];
	else if (key == 0)
		mlx->cam.auto_rot[1] = !mlx->cam.auto_rot[1];
	else if (key == 13)
		mlx->cam.auto_rot[3] = !mlx->cam.auto_rot[3];
	else if (key == 12)
		mlx->cam.view = !mlx->cam.view;
	else if (key == 8)
		update_value_up(mlx, (double *)(&mlx->cam.dist), 5, INT_MAX);
	else if (key == 9)
		update_value_down(mlx, (double *)(&mlx->cam.dist), -5, 10);
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
	{
		img_clean(mlx);
		mlx->img.x = mlx->img.x + WIN_W / 2 + x - mlx->mouse.x;
		mlx->img.y = mlx->img.y + WIN_H / 2 + y - mlx->mouse.y;
		mlx->mouse.x = WIN_W / 2 + x;
		mlx->mouse.y = WIN_H / 2 + y;
		img_draw(mlx);
	}
	else if (mlx->mouse.r && x < WIN_W && y < WIN_H && x > 0 && y > 0)
	{
		img_clean(mlx);
		mlx->cam.angleh = mlx->cam.angleh + 0.01 * (mlx->mouse.x - x);
		mlx->cam.anglev = mlx->cam.anglev - 0.01 * (mlx->mouse.y - y);
		mlx->mouse.x = x;
		mlx->mouse.y = y;
		img_draw(mlx);
	}
	return (0);
}

int	hook_mousedown(int button, int x, int y, t_mlx *mlx)
{
	if (button == 4)
		update_value_up(mlx, &mlx->cam.zoom, 0.1, INT_MAX);
	else if (button == 5 && mlx->cam.zoom - 1 > 0)
		update_value_down(mlx, &mlx->cam.zoom, -0.1, 0);
	else if (button == 1 && x > mlx->ui.x * 2
		&& x < mlx->ui.x * 6 && y > mlx->ui.y - 125
		&& y < mlx->ui.y && mlx->ui.rgbcircle)
	{
		mlx->map.colormin = color_rgb(mlx, x, y, 1);
		img_draw(mlx);
	}
	else if (button == 1 && x > mlx->ui.x * 2 && y < mlx->ui.y - 25)
	{
		mlx->mouse.l = 1;
		mlx->mouse.y = WIN_H / 2 + y;
	}
	else if (button == 1 && x < mlx->ui.x * 2 && y > mlx->ui.y - 25)
		mlx->ui.rgbcircle = !mlx->ui.rgbcircle;
	else if (button == 1 && x < 75 && y < 75)
	{
		update_value_up(mlx, (double *)(&mlx->cam.view), 1, 2);
		/*img_clean(mlx);
		mlx->cam.view = !mlx->cam.view;*/
	}
	else if (button == 2)
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
	if (button == 1)
		update_value_up(mlx, (double *)(&mlx->mouse.l), 1, 1);
	else if (button == 2)
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
