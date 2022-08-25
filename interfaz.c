/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interfaz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:02:24 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/25 18:37:53 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	color_polar(float a, int d)
{
	if (!d)
		return (0);
	if (a <= 255)
		return (trgb(0, (255 - a) * d, a * d, 0));
	else if (a <= 510)
		return (trgb(0, 0, (510 - a) * d, (a - 255)) * d);
	else
		return (trgb(0, (a - 510) * d, 0, (765 - a) * d));
}

int	color_rgb(t_mlx *mlx, int getx, int gety, int d)
{
	float	a;
	int		r;
	float	angle;
	int		x;
	int		y;

	a = 0;
	while (a <= 765)
	{
		r = -1;
		angle = (a * 2 * M_PI) / (3 * 255);
		while (++r < 50)
		{
			x = 100 + r * cos(angle);
			y = mlx->ui.y - 50 + r * sin(angle);
			my_mlx_pixel_put(&mlx->img, x, y, color_polar(a, d));
			if (x != 0 && x == getx && y == gety && mlx->ui.rgbcircle)
				return (color_polar(a, d));
		}
		a += 1;
	}
	return (0);
}

void	circle_draw(t_mlx *mlx, int color, int x, int y)
{
	int		a;
	int		r;
	float	angle;

	a = 0;
	while (a <= 765)
	{
		r = -1;
		angle = (a * 2 * M_PI) / (3 * 255);
		while (++r < 15)
			my_mlx_pixel_put(&mlx->img,
				x + r * sin(angle),
				y + r * cos(angle),
				color);
		a += 1;
	}
	map_repaint(&mlx->map);
}

void	Button_load(t_mlx *mlx)
{
	int		x;
	int		i;

	i = -1;
	while (++i <= 30)
	{
		mlx->ui.Button_file[11] = '0' + i % 10;
		mlx->ui.Button_file[10] = '0' + i / 10;
		mlx->ui.Button[i] = mlx_xpm_file_to_image(&mlx->mlx,
				mlx->ui.Button_file, &x, &x);
	}
}

void	Button_draw(t_mlx *mlx)
{
		mlx_put_image_to_window(mlx->mlx, mlx->win, 
				mlx->ui.Button[mlx->ui.frame], WIN_W - 60, WIN_H - 60);
		if (mlx->ui.frame < 30)
			mlx->ui.frame++;
		else
			mlx->ui.frame = 0;
}

void	put_data(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win,
			WIN_W / 2 - 100, WIN_H - 20, 0xFFFFFF,
			ft_strjoin("Angle H: ",
			ft_strjoin(ft_itoa(mlx->cam.angleh * 180 / M_PI),
			ft_strjoin("  Angle V: ",
			ft_itoa(mlx->cam.anglev * 180 / M_PI)))));
}
