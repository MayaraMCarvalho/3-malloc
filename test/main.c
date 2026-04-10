/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:30:01 by macarval          #+#    #+#             */
/*   Updated: 2026/04/10 20:27:47 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main(int argc, char **argv)
{
	welcome();

	if (argc != 2)
	{
		ft_printf("\n%sUso: %s <numero_do_teste>%s\n\n", BRED, argv[0], RESET);
		// return (1);
	}

	ft_printf("Tamanho da página: %d bytes\n", PAGE_SIZE);

	char *	str = malloc(10 * sizeof(char));
	if (!str)
	{
		ft_printf("%sError: Failed to allocate memory.%s\n\n", BRED, RESET);
		return 1;
	}

	goodbye();
	return 0;
}
