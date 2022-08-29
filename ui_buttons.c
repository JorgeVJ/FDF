/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.buttons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 22:05:40 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/29 15:28:51 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*void	button_load(t_mlx *mlx)
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
}*/

void	images_load(t_mlx *mlx, t_frames *images, char *file, int frames)
{
	int		x;
	int		i;
	int		len;

	images->max = frames;
	len = ft_strlen(file) + 1;
	images->file = malloc(sizeof(char) * (len));
	ft_strlcpy(images->file, file, len); 
	images->images = malloc(sizeof(void *) * (frames + 1));
	i = -1;
	while (++i <= frames)
	{
		images->file[len - 6] = '0' + i % 10;
		images->file[len - 7] = '0' + i / 10;
		images->images[i] = mlx_xpm_file_to_image(&mlx->mlx,
				images->file, &x, &x);
	}
}

void	image_animate(t_mlx *mlx, t_frames *images, int x, int y)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win,
		images->images[images->frame], x, y);
	if (images->frame < images->max)
		images->frame++;
	else
		images->frame = 0;
}

/*void	button_draw(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win,
		mlx->ui.Button[mlx->ui.frame], WIN_W - 60, WIN_H - 60);
	if (mlx->ui.frame < 30)
		mlx->ui.frame++;
	else
		mlx->ui.frame = 0;
}*/

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
