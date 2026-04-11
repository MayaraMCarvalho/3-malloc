/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:30:01 by macarval          #+#    #+#             */
/*   Updated: 2026/04/11 16:08:40 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "malloc.h"
#include "colors.h"

int	main(void)
{
	char	*str;

	str = malloc(10 * sizeof(char));
	if (!str)
	{
		printf("%sError: Failed to allocate memory.%s\n\n", BRED, RESET);
		return (1);
	}

	return (0);
}
