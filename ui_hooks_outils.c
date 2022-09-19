/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_hooks_outils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 23:08:57 by jvasquez          #+#    #+#             */
/*   Updated: 2022/09/02 10:55:34 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	proyections(t_mlx *mlx, int key)
{
	if (key == 84 || key == 86 || key == 88 || key == 91)
		mlx->cam.anglev = 0;
	else if (key == 87)
		mlx->cam.anglev = M_PI_2;
	else if (key == 89 || key == 92 || key == 83 || key == 85)
		mlx->cam.anglev = M_PI_4;
	if (key == 88)
		mlx->cam.angleh = 0;
	else if (key == 91)
		mlx->cam.angleh = M_PI_2;
	else if (key == 86)
		mlx->cam.angleh = M_PI;
	else if (key == 84)
		mlx->cam.angleh = -M_PI_2;
	else if (key == 89)
		mlx->cam.angleh = M_PI_4;
	else if (key == 92)
		mlx->cam.angleh = 3 * M_PI_4;
	else if (key == 83)
		mlx->cam.angleh = 5 * M_PI_4;
	else if (key == 85)
		mlx->cam.angleh = 7 * M_PI_4;
}

void	update_value_up(t_mlx *mlx, double *val, double dv, double max)
{
	img_clean(mlx);
	*val += dv;
	if (*val >= max)
		*val = 0;
	img_draw(mlx);
}

void	update_value_down(t_mlx *mlx, double *val, double dv, double min)
{
	img_clean(mlx);
	*val += dv;
	if (*val <= 0)
		*val = min;
	img_draw(mlx);
}

void	rotations_off(t_mlx *mlx)
{
	int	i;

	i = 4;
	while (--i + 1)
		mlx->cam.auto_rot[i] = 0;
}

void	mouse_left(t_mlx *mlx, int x, int y)
{
	if (x < 75 && y < 75)
	{
		img_clean(mlx);
		mlx->cam.view = !mlx->cam.view;
	}
	if (x < UI_X * 2 && y > mlx->ui.y - 25)
		mlx->ui.rgbcircle = !mlx->ui.rgbcircle;
	else if (x > UI_X * 2
		&& x < UI_X * 6 && y > mlx->ui.y - 125
		&& y < mlx->ui.y && mlx->ui.rgbcircle)
	{
		mlx->map.colormin = color_rgb(mlx, x, y, 1);
		img_draw(mlx);
	}
	else if (x > UI_X * 2 && y < mlx->ui.y - 25)
	{
		mlx->mouse.l = 1;
		mlx->mouse.y = WIN_H / 2 + y;
	}
}
