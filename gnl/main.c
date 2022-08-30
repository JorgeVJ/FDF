/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:26:13 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/19 00:15:34 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		file[6];
	int		i;
	char	*str;

	file[0] = open("0000.png", O_RDONLY);
//	file[1] = open("text2", O_RDONLY);
//	file[5] = open("gnlTester/files/nl", O_RDONLY);
	i = 10;
	while (i--)
	{
		str = get_next_line(file[0]);
		printf("%s", str);
		free(str);
		/*str = get_next_line(file[1]);
		printf("%s", str);
		free(str);*/
	}
}
