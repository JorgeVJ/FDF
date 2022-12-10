/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_vars_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:17:57 by jvasquez          #+#    #+#             */
/*   Updated: 2022/12/10 18:17:59 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/fdf.h"

void	update_int_up(t_mlx *mlx, int *val, int dv, int max)
{
	img_clean(mlx);
	*val += dv;
	if (*val >= max)
		*val = 0;
	img_draw(mlx);
}

// Change a value adding 'dv' and repaint the map.
void	update_value_up(t_mlx *mlx, double *val, double dv, double max)
{
	img_clean(mlx);
	*val += dv;
	if (*val >= max)
		*val = 0;
	img_draw(mlx);
}

// Change a value substracting 'dv' and repaint the map.
void	update_value_down(t_mlx *mlx, double *val, double dv, double min)
{
	img_clean(mlx);
	*val += dv;
	if (*val <= 0)
		*val = min;
	img_draw(mlx);
}
