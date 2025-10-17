/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:02:15 by macarval          #+#    #+#             */
/*   Updated: 2024/10/24 11:53:16 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	char		*final;
	static char	*rest[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = create_buf(fd, rest[fd]);
	rest[fd] = NULL;
	free(rest[fd]);
	if (!line)
		return (NULL);
	final = create_line(line);
	if (BUFFER_SIZE > 1 && ft_strlen(line) > ft_strlen(final))
		rest[fd] = create_rest(line, final);
	free(line);
	return (final);
}
