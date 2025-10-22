/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:30:01 by macarval          #+#    #+#             */
/*   Updated: 2025/10/21 14:34:23 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main(void)
{
	ft_printf("\n%sMalloc rodando%s\n\n", BPURPLE, RESET);

	char *	str = malloc(10 * sizeof(char));
	if (!str)
	{
		ft_printf("%sMalloc falhou%s\n\n", BRED, RESET);
		return 1;
	}

	return 0;
}
