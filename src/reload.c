/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:39:35 by jvasquez          #+#    #+#             */
/*   Updated: 2022/12/10 19:39:35 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Free loaded maps, clean the screen and reload from file.
void	reload(t_mlx *m)
{
	//img_clean(m);
	//mlx_put_image_to_window(m->mlx, m->win, &m->img, 0, 0);
	map_free(&m->map);
	map_free(&m->sphere);
	if (m->ui.menu.hover_on == 0)
		load_file(m, "test_maps/pyramide.fdf");
	if (m->ui.menu.hover_on == 1)
		load_file(m, "test_maps/World.fdf");
	if (m->ui.menu.hover_on == 2)
		load_file(m, "test_maps/julia.fdf");
	if (m->ui.menu.hover_on == 3)
		load_file(m, "test_maps/t1.fdf");
	if (m->ui.menu.hover_on == 4)
		load_file(m, "test_maps/42.fdf");
	m->ui.menu_in = 0;
}
