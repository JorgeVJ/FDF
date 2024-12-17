/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_UI.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:58:33 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/17 15:30:51 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UI_H
# define MLX_UI_H
# define UI_X	35
# define UI_Y	50

# include "fdf_struct.h"
# include "fdf.h"

// void    ui_sphere/_create(t_mlx *mlx);
float	distance(t_point a, t_point b);
void	menu_hover(t_menu *menu, int x, int y);
void	menu_init(t_menu *m, char **texto, t_point pos);
void	menu_display(t_menu *menu);
void	circle_draw(t_mlx *mlx, int color, int x, int y);
int		color_rgb(t_mlx *mlx, int getx, int gety, int d);
int		color_pick(t_mlximg *img, int x, int y);
void	copy_colors_from_map(t_map *dst, t_map src);
void	images_load(t_mlx *mlx, t_frames *images, char *file, int frames);
void	image_animate(t_mlx *mlx, t_frames *images, int x, int y);
void	key_put(t_mlx *mlx, char *str, int x, int y);
void	key_help(t_mlx *mlx);
void	cube_create(t_map *grid, int a);
void	cone_create(t_map *grid, int h, int r);
void	sphere_create(t_map *grid, int r, float *dp);
float	*mapz_to_displacement(t_map map, float scale);
t_map	grid_create(int width, int height);
void	sphere_transform(t_mlx *mlx);
void	scale_z(t_mlx *mlx, int x, int y);
void	mouse_left(t_mlx *mlx, int x, int y);
int		hook_keydown(int key, t_mlx *mlx);
int		hook_mousemove(int x, int y, t_mlx *mlx);
int		hook_mousedown(int button, int x, int y, t_mlx *mlx);
int		hook_mouseup(int button, int x, int y, t_mlx *mlx);
int		hook_rotate(t_mlx *mlx);
void	rotations_off(t_mlx *mlx);
void	auto_rotate(t_mlx *mlx, int key);
void	rotate_cam(t_mlx *mlx, int x, int y);
void	proyections(t_mlx *mlx, int key);
void	fdf_cam_init(t_mlx *mlx);
t_point	cam_pos(t_cam *cam);
#endif
