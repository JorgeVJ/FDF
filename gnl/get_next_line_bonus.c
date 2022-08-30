/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasquez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:08:29 by jvasquez          #+#    #+#             */
/*   Updated: 2022/08/30 17:14:26 by jvasquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_fillbuf(ssize_t *size, int fd)
{
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	*size = read(fd, buf, BUFFER_SIZE);
	if (!*size)
		return (ft_strfree(&buf));
	buf[*size] = '\0';
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*files[4096];
	ssize_t		size;
	char		*str;

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!files[fd])
	{
		files[fd] = ft_fillbuf(&size, fd);
		if (!files[fd])
			return (NULL);
	}
	if (!files[fd][0])
		if (!ft_bufjoin(&files[fd], fd))
			return (ft_strfree(&files[fd]));
	str = ft_getline(&files[fd], fd);
	return (str);
}
