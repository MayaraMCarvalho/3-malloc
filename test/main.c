/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:30:01 by macarval          #+#    #+#             */
/*   Updated: 2026/04/11 18:54:28 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "colors.h"

void	welcome(void);
void	goodbye(void);

int	main(void)
{
	char	*str;

	welcome();

	str = malloc(10 * sizeof(char));
	str = malloc(10 * sizeof(char));
	// str = malloc(128 * sizeof(char));
	// str = malloc(1024 * sizeof(char));
	// str = malloc(1025 * sizeof(char));
	if (!str)
	{
		ft_printf("%sError: Failed to allocate memory.%s\n\n", BRED, RESET);
		return (1);
	}

	show_alloc_mem();

	goodbye();
	return (0);
}
