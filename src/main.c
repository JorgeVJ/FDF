/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:10:22 by jvasquez          #+#    #+#             */
/*   Updated: 2022/11/25 20:17:11 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	leaks(void)
{
	system("leaks fdf");
}
	//atexit(leaks);

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc > 2 || argc < 2)
	{
		write(1, "Are you introducing one map?", 28);
		return (0);
	}
	fdf_init(&mlx, argv[argc * 0 + 1]);
	mlx_hook(mlx.win, 4, 0, hook_mousedown, &mlx);
	mlx_hook(mlx.win, 5, 0, hook_mouseup, &mlx);
	mlx_hook(mlx.win, 6, 0, hook_mousemove, &mlx);
	mlx_hook(mlx.win, 17, 0, hook_exit, &mlx);
	mlx_key_hook(mlx.win, hook_keydown, &mlx.mlx);
	mlx_loop_hook(mlx.mlx, hook_rotate, &mlx);
	mlx_loop(mlx.mlx);
}
