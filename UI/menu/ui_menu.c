/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 01:26:11 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/17 15:30:51 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/fdf.h"

/*void	rectangle(t_mlx *m, t_point c, char *texto, int act)
{
	int		i;
	int		j;
	t_point	d;

	d.x = 100;
	d.y = 30;
	j = d.x;
	while (j--)
	{
		i = d.y;
		while (i--)
			my_mlx_pixel_put(&m->img, j + c.x - d.x / 2, i + c.y - d.y / 2,
				0xBBBBBB + (0x4400 - 0xAA00AA) * act);
	}
	mlx_string_put(m->mlx, m->win, c.x - (ft_strlen(texto) * 9) / 2,
		c.y - 15 / 2, 0xFFF0 * !act, texto);
}*/

/*void	map_explode(t_mlximg *img)
{
	char	*dst;
	unsigned int	color;
	t_point	p;
	static float	d = 0;

	p.x = 299;
	while (++p.x < WIN_W - 500)
	{
		p.y = -1;
		while (++p.y < WIN_H)
		{
			dst = img->addr + ((int)p.y * img->line_length + (int)p.x * (img->bits_per_pixel / 8));
			color = *(unsigned int *)dst;
			if (color != 0)
			{
				*(unsigned int *)dst = 0;
				dst = img->addr + ((int)(p.y + 10 * sin(d)) * img->line_length + (int)(p.x + 1 * cos(d)) * (img->bits_per_pixel / 8));
				*(unsigned int *)dst = color;
			}
		}
	}
	d += 0.01;
}*/

float	scalar(t_point a, t_point b, float max, float min)
{
	float	scalar;

	scalar = (b.x * a.x + b.y * a.y + b.z * a.z);
	if (scalar > max)
		scalar = max;
	else if (scalar < min)
		scalar = min;
	return (scalar);
}

void	button_normals(t_menu *m, t_button *b)
{
	int	i;
	int	j;

	b->nm = malloc(sizeof(t_point *) * b->dim.y);
	i = -1;
	while (++i < b->dim.y)
	{
		b->nm[i] = malloc(sizeof(t_point) * b->dim.x);
		j = -1;
		while (++j < b->dim.x)
		{
			if ((j >= 15 && j <= 85) || distance(point_fill(85, 0, 0), point_fill(j, 15 - i, 0)) <= 15 ||
				distance(point_fill(15, 0, 0), point_fill(j, 15 - i, 0)) <= 15)
					b->nm[i][j] = m->n.gen[300 + (int)(250 * sin(j * M_PI / 100 - M_PI_2))][300 + (int)(250 * sin(i * M_PI / 50 - M_PI_2))];
			else
			{
				b->nm[i][j].x = 0;
				b->nm[i][j].y = 0;
				b->nm[i][j].z = -1;
			}
		}
	}
}

void	button_draw(t_menu *menu, t_button b, int act)
{
	int		i;
	int		j;
	int		light;
	t_point	sun;

	sun = point_fill(menu->mouse.x - WIN_W / 2 + b.dim.x / 2, - (menu->mouse.y - b.center.y) + b.dim.y / 2, 0);
	normalize(&sun);
	j = b.dim.x;
	while (j--)
	{
		i = b.dim.y;
		while (i--)
		{
			light = (int)(255 * scalar(b.nm[i][j], sun, 1, 0.2));
			if (b.nm[i][j].z >= 0)
				my_mlx_pixel_put(menu->img, j + b.center.x - b.dim.x / 2, i + b.center.y - b.dim.y / 2,
					trgb(0, light / (1 + act * 20), light, light / (1 + act * 20)));
		}
	}
	mlx_string_put(menu->mlx, menu->win, b.center.x - (ft_strlen(b.text) * 9) / 2,
		b.center.y - 15 / 2, 0xFFF0 * !act, b.text);
}


void	menu_init(t_menu *m, char **texto, t_point pos)
{
	m->size = 0;
	float i = 0;
	float step = 2 * M_PI / (5);
	//t_point	center = pos;
	while (texto[m->size])
	{
		m->button[m->size].id = m->size;
		m->button[m->size].center = pos;
		m->button[m->size].text = texto[m->size];
		m->button[m->size].dim.x = 100;
		m->button[m->size].dim.y = 30;
		button_normals(m, &m->button[m->size]);
		pos.y = pos.y + 40;
		//pos.x = center.x + 150 * sin(i);
		//pos.y = center.y + 150 * cos(i);
		i += step;
		m->size++;
	}
	m->mouse.x = 10;
	m->mouse.y = 10;
	free(texto);
}

void	menu_display(t_menu *menu)
{
	int	i;
	t_image *img;

	img = (t_image *)menu->img;
	i = -1;
	mlx_put_image_to_window(menu->mlx, menu->win, img->img, 0, 0);
	while (++i < menu->size)
		button_draw(menu, menu->button[i], (i == menu->hover_on));
}

void	menu_hover(t_menu *menu, int x, int y)
{
	int	i;

	if (x > menu->button[0].center.x - 50 && x < menu->button[0].center.x + 50)
	{
		i = -1;
		while (++i < menu->size)
		{
			if (y > menu->button[i].center.y - 15
				&& y < menu->button[i].center.y + 15)
				menu->hover_on = i;
		}
	}
	menu->mouse.x = x;
	menu->mouse.y = y;
	menu_display(menu);
}
