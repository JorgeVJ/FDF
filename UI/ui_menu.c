/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 01:26:11 by jvasquez          #+#    #+#             */
/*   Updated: 2022/12/11 01:26:11 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/fdf.h"

void	rectangle(t_mlx *m, t_point c, char *texto, int act)
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
}

void	menu_init(t_menu *m, char **texto, t_point pos)
{
	m->size = 0;
	while (texto[m->size])
	{
		m->button[m->size].id = m->size;
		m->button[m->size].center = pos;
		m->button[m->size].text = texto[m->size];
		pos.y = pos.y + 50;
		m->size++;
	}
	free(texto);
}

void	menu_display(t_mlx *m, t_menu *menu)
{
	int	i;

	i = -1;
	mlx_put_image_to_window(m->mlx, m->win, m->img.img, 0, 0);
	while (++i < menu->size)
		rectangle(m, menu->button[i].center, menu->button[i].text,
			(i == menu->hover_on));
}

void	menu_hover(t_mlx *m, t_menu *menu, int x, int y)
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
	menu_display(m, menu);
}
