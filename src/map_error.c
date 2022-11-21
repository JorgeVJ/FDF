/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:15:43 by jvasquez          #+#    #+#             */
/*   Updated: 2022/11/18 21:15:47 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_error(int height, int width)
{
	if (height <= 1 || width <= 1)
	{
		write(1, "Mapa invalido", 14);
		exit(EXIT_SUCCESS);
	}
}

void	str_error(char *str, int pos)
{
	char	c;

	if (str[pos] == ' ' || str[pos] == '\n')
		pos += 1;
	c = str[pos];
	if (c != '-' && c != '+' && c != ','
		&& c != '\0' && !(c >= '0' && c <= '9'))
	{
		write(1, "Caracter invalido", 18);
		exit(EXIT_SUCCESS);
	}
}
