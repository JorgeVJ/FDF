/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:20:05 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/25 17:54:08 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hook_keydown(int key, t_mlx *mlx)
{
	(void)mlx;
	img_clean(mlx);
	if (key == 84 || key == 86 || key == 88 || key == 91)
		mlx->cam.anglev = 0;	
	else if (key == 87)
		mlx->cam.anglev = M_PI_2;
	else if (key == 53)
		exit(EXIT_SUCCESS);
	else if (key == 2)
		mlx->cam.auto_rot = !mlx->cam.auto_rot;
	else if (key == 1)
		mlx->cam.auto_rotv = !mlx->cam.auto_rotv;
	else if (key == 0)
		mlx->cam.view = !mlx->cam.view;
	if (key == 88)
		mlx->cam.angleh = 0;
	else if (key == 91)
		mlx->cam.angleh = M_PI_2;
	else if (key == 86)
		mlx->cam.angleh = M_PI;
	else if (key == 84)
		mlx->cam.angleh = -M_PI_2;
	img_draw(mlx);
	printf("%d\n",  key);
	return (0);
}

int	hook_mousemove(int x, int y, t_mlx *mlx)
{
	if (x > WIN_W - 60 && x < WIN_W && y > WIN_H - 60 && y < WIN_H)
		mlx->ui.mouse_in = 1;
	else
		mlx->ui.mouse_in = 0;
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
	(void)mlx;
	(void)x;
	(void)y;
	if (button == 4)
		update_value(mlx, (double *)(&mlx->cam.zoom), 1, INT_MAX);
	else if (button == 5)
		update_value(mlx, (double *)(&mlx->cam.zoom), -1, INT_MAX);
	else if (button == 1 && x > mlx->ui.x * 2
		&& x < mlx->ui.x * 6 && y > mlx->ui.y - 125
		&& y < mlx->ui.y && mlx->ui.rgbcircle) 
	{
		mlx->map.colormin =	color_rgb(mlx, x, y, 1);
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
		img_clean(mlx);
		mlx->cam.view = !mlx->cam.view;
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
		update_value(mlx, (double *)(&mlx->mouse.l), 42, 0);
	else if (button == 2)
		mlx->mouse.r = 0;
	return (0);
}

int	hook_rotate(t_mlx *mlx)
{
	mlx->ui.time++;
	if (!(mlx->ui.time % 630) && mlx->ui.mouse_in)
		Button_draw(mlx);
	if (!(mlx->ui.time % 420) && mlx->cam.auto_rot)
		update_value(mlx, &mlx->cam.angleh, 0.01, 2 * M_PI);
	if (!(mlx->ui.time % 420) && mlx->cam.auto_rotv)
		update_value(mlx, &mlx->cam.anglev, 0.01, 2 * M_PI);
	if (mlx->ui.time > 1678)
		mlx->ui.time = 0;
	return (0);
}
