/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3++.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:57:29 by macarval          #+#    #+#             */
/*   Updated: 2026/04/22 17:15:40 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <string.h>

void	print(char *s)
{
	write(1, s, strlen(s));
}

int	main(void)
{
	char	*addr1;
	char	*addr2;
	char	*addr3;

	addr1 = (char *)malloc(16 * 1024 * 1024);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr2 = (char *)malloc(16 * 1024 * 1024);
	addr3 = (char *)realloc(addr1, 128 * 1024 * 1024);
	addr3[127 * 1024 * 1024] = 42;
	print(addr3);
	return (0);
}
