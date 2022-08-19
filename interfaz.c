/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interfaz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:02:24 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/19 20:19:40 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*int	color_pick(t_img *img, int x, int y)
{
	char *dst;
	unsigned int		color;

	if (x < 0 || x >= WIN_W|| y < 0 || y >= WIN_H)
		return (0);
	printf("%p\n", img->addr);
	printf("x:%d y:%d\n",  x, y);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	//dst = img->addr + (y * img->line_length + x * img->bits_per_pixel);
	//printf("color%X\n",  *(unsigned int *)dst);
	//printf("color%p\n",  *dst);
	color = (unsigned int)dst & 0xFFFFFFFF;
	printf("color%d\n",  color);
	return(*(unsigned int *)dst);

	float a;
	a = 0;
	if (y != 625)
	{
		a = atan((y - 625) / abs((x - 100))) * (3 * 255) / (2 * M_PI);
		printf("angle:%f\n", atan((y - 625) / abs(x - 100)));
	}
	else if (x > 100)
		a = 180 * (3 * 255) / (2 * M_PI);
	printf("a:%f\n", a);
	if (a <= 255) 
	{
		mlx->map.colormin =	trgb(0, (255 - a), a, 0);
		printf("a < 255: r%f g%f\n", (255 - a), a);
	}
	else if (a <= 510)
		mlx->map.colormin = trgb(0, 0, (510 - a), (a - 255));
	else
		mlx->map.colormin = trgb(0, (a - 510), 0, (765 - a));
}*/

//int	color_in_rgb(int x, int y)

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
			if (x != 0 && x == getx && y == gety)
				return (color_polar(a, d));
		}
		a += 1;
	}
	return (0);
}

void	color_select(t_mlx *mlx)
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
				mlx->ui.x + r * sin(angle),
				mlx->ui.y + r * cos(angle),
				mlx->map.colormin);
		a += 1;
	}
	map_repaint(&mlx->map);
}
