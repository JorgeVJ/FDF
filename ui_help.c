/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:01:07 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/30 08:38:14 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_put(t_mlx *mlx, char *texto, int x, int y)
{
	int	len;

	len = ft_strlen(texto);
	mlx->ui.keys.frame = 0;
	image_animate(mlx, &mlx->ui.keys, x, y);
	mlx_string_put(mlx->mlx, mlx->win, x + 36 - (len * 8)
		/ 2, y + 20, 0xFFFFFF, texto);
}

void	numpad_put(t_mlx *mlx, int x, int y)
{
	mlx_string_put(mlx->mlx, mlx->win, x + 100, y - 30, 0xFFFFFF, "Views");
	key_put(mlx, "npd7", x, y);
	key_put(mlx, "npd4", x, y + 70);
	key_put(mlx, "npd1", x, y + 140);
	key_put(mlx, "npd8", x + 80, y);
	key_put(mlx, "npd5", x + 80, y + 70);
	key_put(mlx, "npd2", x + 80, y + 140);
	key_put(mlx, "npd9", x + 160, y);
	key_put(mlx, "npd6", x + 160, y + 70);
	key_put(mlx, "npd3", x + 160, y + 140);
}

void	mouse_put(t_mlx *mlx, char *texto, int x, int y)
{
	int	len;

	len = ft_strlen(texto);
	image_animate(mlx, &mlx->ui.keys, x, y);
	mlx_string_put(mlx->mlx, mlx->win, x + 25 - (len * 9)
		/ 2, y - 20, 0xFFFFFF, texto);
}

void	key_help(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, 70, 40, 0xFFFFFF, "<- Change view");
	mlx_string_put(mlx->mlx, mlx->win, 70, WIN_H - 40,
		0xFFFFFF, "<- Change color");
	mlx_string_put(mlx->mlx, mlx->win, 200, 100, 0xFFFFFF, "Auto rotation");
	key_put(mlx, "A", 150, 200);
	key_put(mlx, "D", 310, 200);
	key_put(mlx, "W", 230, 130);
	key_put(mlx, "S", 230, 200);
	numpad_put(mlx, 500, 120);
	mlx_string_put(mlx->mlx, mlx->win, 245, 300, 0xFFFFFF, "Zoom");
	mouse_put(mlx, "Out", 200, 350);
	mouse_put(mlx, "In", 270, 350);
	mouse_put(mlx, "Desplazar", 235, 450);
	mouse_put(mlx, "Rotar", 235, 550);
	key_put(mlx, "Q", 500, 400);
	mlx_string_put(mlx->mlx, mlx->win, 600, 420, 0xFFFFFF, "Change view");
	key_put(mlx, "C", 500, 470);
	mlx_string_put(mlx->mlx, mlx->win, 600, 490, 0xFFFFFF, "Conic effect-");
	key_put(mlx, "V", 500, 540);
	mlx_string_put(mlx->mlx, mlx->win, 600, 560, 0xFFFFFF, "Conic effect+");
}
