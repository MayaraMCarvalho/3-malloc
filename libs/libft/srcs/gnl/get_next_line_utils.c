/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:40:09 by macarval          #+#    #+#             */
/*   Updated: 2024/10/24 11:53:41 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_find(char *str)
{
	size_t	i;

	if (str[0] != '\0')
	{
		i = 0;
		while (i < ft_strlen(str))
		{
			if (str[i] == '\n' || str[i] == '\0')
				return (1);
			i++;
		}
	}
	return (0);
}

char	*create_rest(char *line, char *final)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (line[i] == final[i])
		i++;
	res = (char *) malloc ((ft_strlen(line) - i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (line[i])
		res[j++] = line[i++];
	res[j] = '\0';
	return (res);
}

char	*create_line(char *str)
{
	int		find;
	int		i;
	char	*line;

	i = -1;
	find = 0;
	if (str[0] == '\0' || !str)
		return (NULL);
	while (str[find] != '\n' && str[find] != '\0')
		find++;
	line = malloc ((find + 2) * sizeof(char));
	if (!line)
		return (NULL);
	while (i++ < find)
		line[i] = str[i];
	line[i] = '\0';
	return (line);
}

char	*create_buf(int fd, char *rest)
{
	char	*tmp;
	char	*buf;
	int		rbyte;

	rbyte = 1;
	buf = ft_strdup(rest);
	free(rest);
	while (rbyte > 0)
	{
		tmp = malloc ((BUFFER_SIZE + 1) * sizeof(char));
		if (!tmp)
			return (NULL);
		ft_bzero(tmp, BUFFER_SIZE + 1);
		rbyte = read(fd, tmp, BUFFER_SIZE);
		if (rbyte < 1)
		{
			free(tmp);
			return (buf);
		}
		if (rbyte > 0 && (ft_find(tmp)))
			rbyte = -2;
		buf = ft_strjoin(buf, tmp);
		free(tmp);
	}
	return (buf);
}
