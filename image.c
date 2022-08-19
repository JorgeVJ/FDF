/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:24:10 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/19 20:36:47 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	img_new(t_mlx *mlx)
{
	mlx->img.img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	img_draw(mlx);
}

void	img_draw(t_mlx *mlx)
{
	img_fill(mlx, mlx->img.x, mlx->img.y, 1);
	if (mlx->ui.rgbcircle)
		color_rgb(mlx, 0, 0, mlx->ui.rgbcircle);
	color_select(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

void	img_clean(t_mlx *mlx)
{
	color_rgb(mlx, 0, 0, mlx->ui.rgbcircle);
	img_fill(mlx, mlx->img.x, mlx->img.y, 0);
}

void	img_fill(t_mlx *mlx, int gapx, int gapy, int trgb)
{
	int		i;
	t_point	a;
	t_point	b;
	t_map	m;

	m = mlx->map;
	i = 0;
	while (i < m.size)
	{
		a = point_move(&m, i, -m.width / 2, -m.height / 2);
		b = point_project(mlx, a, gapx, gapy);
		if (i > 0 && m.xyzc[0][i] == m.xyzc[0][i - 1])
			line (mlx, b.x, b.y, trgb * m.xyzc[3][i]);
		mlx->line.xo = b.x;
		mlx->line.yo = b.y;
		if (i + m.height + 1 <= m.size)
		{
			a = point_move(&m, i + m.height + 1, -m.width / 2, -m.height / 2);
			b = point_project(mlx, a, gapx, gapy);
			line (mlx, b.x, b.y, trgb * m.xyzc[3][i]);
		}
		i++;
	}
}
