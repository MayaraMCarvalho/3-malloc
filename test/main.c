/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:30:01 by macarval          #+#    #+#             */
/*   Updated: 2026/04/11 17:21:59 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "malloc.h"
#include "colors.h"

void	welcome(void);
void	goodbye(void);

int	main(void)
{
	char	*str;

	welcome();

	str = malloc(10 * sizeof(char));
	if (!str)
	{
		printf("%sError: Failed to allocate memory.%s\n\n", BRED, RESET);
		return (1);
	}

	goodbye();
	return (0);
}
