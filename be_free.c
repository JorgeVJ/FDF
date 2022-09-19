/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   be_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 08:44:34 by jvasquez          #+#    #+#             */
/*   Updated: 2022/09/05 14:55:25 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*void	be_free(...)
{
	va_list	args;

	va_start(args, i);

	va_end(args);
	return (size);
}*/

char	*join_free(char *a, char *b)
{
	char	*join;

	join = ft_strjoin(a, b);
	str_be_free(b);
	return (join);
}

void	str_be_free(char *str)
{
	if (str)
	{
		free (str);
		str = NULL;
	}
}

void	ptr_be_free(char **str)
{
	if (str)
	{
		free (str);
		str = NULL;
	}
}

void	map_free(int **map)
{
	if (map)
	{
		free (map);
		map = NULL;
	}
}
