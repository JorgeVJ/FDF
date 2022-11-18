/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interfaz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:02:24 by jvasquez          #+#    #+#             */
/*   Updated: 2022/11/15 20:48:01 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/fdf.h"

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
			my_mlx_pixel_put(&mlx->img, (int)x, (int)y, color_polar(a, d));
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
				(int)(x + r * sin(angle)),
				(int)(y + r * cos(angle)),
				color);
		a += 1;
	}
	map_repaint(&mlx->map);
}

int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
