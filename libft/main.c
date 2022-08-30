/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 20:30:54 by jvasquez          #+#    #+#             */
/*   Updated: 2022/07/21 18:57:32 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(void)
{
	char **expected = ft_split("\0aa\0bbb", '\0');
	for (int i = 0; expected[i]; i++)
	{
		if (expected[i] != ((void *)0))
			printf("Falla\n");
	}
		printf("Pasa\n");
}
