/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:40:05 by macarval          #+#    #+#             */
/*   Updated: 2022/05/28 00:35:54 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# include "libft.h"

# define BUFFER_SIZE	25

char	*get_next_line(int fd);
int		ft_find(char *str);
char	*create_rest(char *line, char *final);
char	*create_line(char *str);
char	*create_buf(int fd, char *rest);

#endif
