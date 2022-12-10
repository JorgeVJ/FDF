/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:28:48 by jvasquez          #+#    #+#             */
/*   Updated: 2022/11/16 11:44:27 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_UTILS_H
# define FDF_UTILS_H

# include "fdf_struct.h"
# include "fdf.h"

void	str_be_free(char *str);
void	nbr_be_free(float *nbr);
char	*join_free(char *a, char *b);
int		ft_atoi_pos(char *str, int *pos);
int		atoi_hexa_pos(char *str, int *pos);
void	update_int_up(t_mlx *mlx, int *val, int dv, int max);
void	update_value_up(t_mlx *mlx, double *val, double dv, double max);
void	update_value_down(t_mlx *mlx, double *val, double dv, double min);
#endif
