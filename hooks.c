/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:20:05 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/19 20:49:02 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hook_keydown(int key, t_mlx *mlx)
{
	(void)mlx;
	if (key == 53)
		exit(EXIT_SUCCESS);
	if (key == 2)
		mlx->cam.auto_rot = !mlx->cam.auto_rot;
	if (key == 0)
		printf(" key0\n");
	return (0);
}

int	hook_mousemove(int x, int y, t_mlx *mlx)
{
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
	{
		img_clean(mlx);
		mlx->cam.zoom++;
		img_draw(mlx);
	}
	else if (button == 5)
	{
		img_clean(mlx);
		mlx->cam.zoom--;
		img_draw(mlx);
	}
	else if (button == 1 && x > mlx->ui.x * 2
		&& x < mlx->ui.x * 6 && y > mlx->ui.y - 125 && y < mlx->ui.y) 
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
	{	
		img_clean(mlx);
		mlx->mouse.l = 0;
		img_draw(mlx);
	}
	else if (button == 2)
		mlx->mouse.r = 0;
	return (0);
}

int	hook_rotate(t_mlx *mlx)
{
	if (mlx->cam.auto_rot)
	{
		img_clean(mlx);
		mlx->cam.angleh += 0.01;
		img_draw(mlx);
	}
	return (0);
}
