/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:23:20 by macarval          #+#    #+#             */
/*   Updated: 2026/04/11 18:45:33 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

static void	print_blocks(t_zone *zone)
{
	t_block	*current;

	current = zone->blocks;
	while (current)
	{
		ft_printf("0x%X - 0x%X : %u bytes\n",
			(void *)(current + 1),
			(void *)((char *)(current + 1) + current->size),
			current->size);
		current = current->next;
	}
}

void	show_alloc_mem(void)
{
	ft_printf("TINY : 0x%X\n", (void *)g_malloc.tiny);
	if (g_malloc.tiny)
		print_blocks(g_malloc.tiny);

	ft_printf("SMALL : 0x%X\n", (void *)g_malloc.small);
	if (g_malloc.small)
		print_blocks(g_malloc.small);

	ft_printf("LARGE : 0x%X\n", (void *)g_malloc.large);
	if (g_malloc.large)
		print_blocks((t_zone *)g_malloc.large);
}


// A visualização será formatada por endereços crescentes, como:

	// TINY : 0xA0000
	// 0xA0020 - 0xA004A : 42 bytes
	// 0xA006A - 0xA00BE : 84 bytes
	// SMALL : 0xAD000
	// 0xAD020 - 0xADEAD : 3725 bytes
	// LARGE : 0xB0000
	// 0xB0020 - 0xBBEEF : 48847 bytes
	// Total : 52698 bytes

