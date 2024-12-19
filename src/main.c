/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <jvasquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:10:22 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/19 17:15:21 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Only MAC
void	leaks(void)
{
	system("leaks -q fdf");
}
	atexit(leaks);
*/

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	(void)argv;
	if (argc > 2 || argc < 2)
	{
		write(1, "Are you introducing one map?", 28);
		return (0);
	}
	normal_generic(&mlx);
	mlx.ui.menu.n.gen = mlx.n.gen;
	fdf_init(&mlx, argv[argc * 0 + 1]);
	mlx_hook(mlx.win, 06, (1L << 6), hook_mousemove, &mlx);
	mlx_hook(mlx.win, 04, (1L << 2), hook_mousedown, &mlx);
	mlx_hook(mlx.win, 05, (1L << 3), hook_mouseup, &mlx);
	mlx_hook(mlx.win, 02, (1L << 0), hook_keydown, &mlx);
	mlx_loop_hook(mlx.mlx, hook_rotate, &mlx);
	mlx_loop(mlx.mlx);
}

