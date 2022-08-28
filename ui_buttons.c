/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.buttons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 22:05:40 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/26 17:08:08 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	button_load(t_mlx *mlx)
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

void	button_draw(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win,
		mlx->ui.Button[mlx->ui.frame], WIN_W - 60, WIN_H - 60);
	if (mlx->ui.frame < 30)
		mlx->ui.frame++;
	else
		mlx->ui.frame = 0;
}

void	str_be_free(char *str)
{
	if (str)
	{
		free (str);
		str = NULL;
	}
}

char	*join_free(char *a, char *b)
{
	char	*join;

	join = ft_strjoin(a, b);
	str_be_free(b);
	return (join);
}

void	put_data(t_mlx *mlx)
{
	char	*data;
	char	*a;
	char	*b;

	a = join_free("Angle H: ", ft_itoa(mlx->cam.angleh * 180 / M_PI));
	b = join_free("  Angle V: ", ft_itoa(mlx->cam.anglev * 180 / M_PI));
	data = join_free(a, b);
	str_be_free(a);
	mlx_string_put(mlx->mlx, mlx->win,
		WIN_W / 2 - 100, WIN_H - 20, 0xFFFFFF, data);
	str_be_free(data);
}
