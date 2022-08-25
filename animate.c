/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:30:59 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/25 17:54:00 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_value(t_mlx *mlx, double *val, double dv, double max)
{
	img_clean(mlx);
	*val += dv;
	if (*val >= max)
		*val = 0;
	img_draw(mlx);
}
