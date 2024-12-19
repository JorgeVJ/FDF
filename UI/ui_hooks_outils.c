/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_hooks_outils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <jvasquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 23:08:57 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/19 17:14:10 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/fdf.h"

// Angle set for projections (called using numpad).
void	proyections(t_mlx *mlx, int key)
{
	if (key == XK_KP_2 || key == XK_KP_4 || key == XK_KP_6 || key == XK_KP_8)
		mlx->cam.anglev = 0;
	else if (key == XK_KP_5)
		mlx->cam.anglev = M_PI_2;
	else if (key == XK_KP_7 || key == XK_KP_9 || key == XK_KP_1 || key == XK_KP_3)
		mlx->cam.anglev = M_PI_4;
	if (key == XK_KP_6)
		mlx->cam.angleh = 0;
	else if (key == XK_KP_8)
		mlx->cam.angleh = M_PI_2;
	else if (key == XK_KP_4)
		mlx->cam.angleh = M_PI;
	else if (key == XK_KP_2)
		mlx->cam.angleh = -M_PI_2;
	else if (key == XK_KP_7)
		mlx->cam.angleh = M_PI_4;
	else if (key == XK_KP_9)
		mlx->cam.angleh = 3 * M_PI_4;
	else if (key == XK_KP_1)
		mlx->cam.angleh = 5 * M_PI_4;
	else if (key == XK_KP_3)
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
	else if (x > UI_X * 2 && y < mlx->ui.y - 25 && !mlx->ui.menu_in)
		mlx->mouse.l = 1;
}
