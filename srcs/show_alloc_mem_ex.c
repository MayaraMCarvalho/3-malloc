/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:54:19 by macarval          #+#    #+#             */
/*   Updated: 2026/04/22 16:18:46 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

/// @brief Prints a hexadecimal dump of the allocated block's data, showing up
/// to 16 bytes for better visualization of the memory content.
/// @param ptr A pointer to the start of the allocated block's data.
/// @param size The size of the allocated block.
static void	print_hexdump(unsigned char *ptr, size_t size)
{
	size_t	i;
	size_t	limit;

	i = -1;
	limit = size;
	if (limit >= 16)
		limit = 16;
	ft_printf("        -> Data: ");
	while (++i < limit)
	{
		if (ptr[i] < 16)
			ft_printf("0");
		ft_printf("%X ", ptr[i]);
	}
	if (size > 16)
		ft_printf("...");
	ft_printf("\n\n");
}

/// @brief Prints the details of each block in the given zone, including its
/// status (allocated or free), memory addresses, size, and a hexadecimal dump
/// of the data for allocated blocks.
/// @param blocks A pointer to the first block in the zone's linked
/// list of blocks.
static void	print_blocks_ex(t_block *blocks)
{
	t_block	*current;

	current = blocks;
	while (current)
	{
		if (current->status == ALLOCATED)
		{
			ft_printf("%s[ALLOCATED]%s %p - %p : %u bytes\n",
				GREEN, RESET,
				(void *)(current + 1),
				(void *)((char *)(current + 1) + current->size),
				(unsigned int)current->size);
			print_hexdump((unsigned char *)(current + 1), current->size);
		}
		else
		{
			ft_printf("%s[FREE]     %s %p - %p : %u bytes\n",
				RED, RESET,
				(void *)(current + 1),
				(void *)((char *)(current + 1) + current->size),
				(unsigned int)current->size);
		}
		current = current->next;
	}
}

/// @brief Prints a detailed memory dump of all allocated and free blocks in
/// the tiny, small, and large zones, including their addresses, sizes,
/// statuses, and a hexadecimal dump of the data for allocated blocks,
/// providing a comprehensive view of the memory state.
/// @param zone A pointer to the first zone in the linked list of zones to be
/// printed.
/// @param zone_name A string representing the name of the zone (e.g., "TINY",
/// "SMALL") for labeling the output.
static void	print_zones_ex(t_zone *zone, char *zone_name)
{
	while (zone)
	{
		ft_printf("\n%s%s : %p%s\n", CYAN, zone_name, (void *)zone, RESET);
		print_blocks_ex(zone->blocks);
		zone = zone->next;
	}
}

/// @brief Displays a detailed memory dump of all allocated and free blocks in
/// the tiny, small, and large zones, including their addresses, sizes,
/// statuses, and a hexadecimal dump of the data for allocated blocks. This
/// function provides a comprehensive view of the memory state, allowing for
/// better visualization and debugging of the allocator's behavior.
/// @param void No parameters.
void	show_alloc_mem_ex(void)
{
	ft_printf("\n%s=== DETAILED MEMORY DUMP ===%s\n", PURPLE, RESET);
	print_zones_ex(g_malloc.tiny, "TINY");
	print_zones_ex(g_malloc.small, "SMALL");
	if (g_malloc.large)
	{
		ft_printf("\n%sLARGE : %p%s\n", CYAN, (void *)g_malloc.large, RESET);
		print_blocks_ex(g_malloc.large);
	}
	ft_printf("%s=================================%s\n\n", PURPLE, RESET);
}
