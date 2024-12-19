/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <jvasquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:13:19 by jvasquez          #+#    #+#             */
/*   Updated: 2024/12/18 22:54:34 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char			*temp;
	unsigned int	i;

	if (!str || start > ft_strlen(str))
		return (NULL);
	if (ft_strlen(str) + 1 <= (len + start))
		len = ft_strlen(str);
	if (start > ft_strlen(str) || !*str)
		return (ft_strdup(""));
	temp = ft_calloc(1, sizeof(char) * (len + 1));
	if (!temp)
		return (NULL);
	i = -1;
	while (++i < len)
		temp[i] = str[start + i];
	return (temp);
}
