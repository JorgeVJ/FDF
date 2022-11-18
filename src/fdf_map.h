/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:21:51 by jvasquez          #+#    #+#             */
/*   Updated: 2022/11/16 11:52:25 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_MAP_H
# define FDF_MAP_H

# include "fdf_struct.h"
# include "fdf.h"

void	map_fill(t_map *map, char *dir);
int		map_deltaz(t_map *map);
void	map_color(t_map *map);
void	map_repaint(t_map *map);
void	map_limits(t_map *m);
void	map_scale(t_map *map, float scale);
void	map_free(int **map);
int		**map_size(char *dir, int *width, int *height);
void	move_map(t_mlx *mlx, int x, int y);
#endif
