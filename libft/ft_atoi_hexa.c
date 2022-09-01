/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:35:23 by jvasquez          #+#    #+#             */
/*   Updated: 2022/09/01 21:35:42 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	atoi_hexa(char *str)
{
	int	sum;

	sum = 0;
	while (*str == '0' || *str == 'x')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			sum = sum * 16 + *str - '0';
		else if (*str >= 'A' && *str <= 'F')
			sum = sum * 16 + *str - 'A' + 10;
		else if (*str >= 'a' && *str <= 'f')
			sum = sum * 16 + *str - 'a' + 10;
		str++;
	}
	return (sum);
}
