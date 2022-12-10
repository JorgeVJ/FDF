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

#include "../src/fdf.h"

// Angle set for projections (called using numpad).
void	proyections(t_mlx *mlx, int key)
{
	if (key == NPD_2 || key == NPD_4 || key == NPD_6 || key == NPD_8)
		mlx->cam.anglev = 0;
	else if (key == NPD_5)
		mlx->cam.anglev = M_PI_2;
	else if (key == NPD_7 || key == NPD_9 || key == NPD_1 || key == NPD_3)
		mlx->cam.anglev = M_PI_4;
	if (key == NPD_6)
		mlx->cam.angleh = 0;
	else if (key == NPD_8)
		mlx->cam.angleh = M_PI_2;
	else if (key == NPD_4)
		mlx->cam.angleh = M_PI;
	else if (key == NPD_2)
		mlx->cam.angleh = -M_PI_2;
	else if (key == NPD_7)
		mlx->cam.angleh = M_PI_4;
	else if (key == NPD_9)
		mlx->cam.angleh = 3 * M_PI_4;
	else if (key == NPD_1)
		mlx->cam.angleh = 5 * M_PI_4;
	else if (key == NPD_3)
		mlx->cam.angleh = 7 * M_PI_4;
}

// Turn off all the rotations.
void	rotations_off(t_mlx *mlx)
{
	int	i;

	i = 4;
	while (--i + 1)
		mlx->cam.auto_rot[i] = 0;
}

// Actions to be taken when left click is pressed.
void	mouse_left(t_mlx *mlx, int x, int y)
{
	if (x < 75 && y < 75)
	{
		img_clean(mlx);
		update_int_up(mlx, &mlx->cam.view, 1, 3);
	}
	if (x < UI_X * 2 && y > mlx->ui.y - 25)
		mlx->ui.rgbcircle = !mlx->ui.rgbcircle;
	else if (x > UI_X * 2
		&& x < UI_X * 6 && y > mlx->ui.y - 125
		&& y < mlx->ui.y && mlx->ui.rgbcircle)
	{
		mlx->map.colormin = color_rgb(mlx, x, y, 1);
		map_repaint(&mlx->map);
		img_draw(mlx);
	}
	else if (x > UI_X * 2 && y < mlx->ui.y - 25)
		mlx->mouse.l = 1;
}
