/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:23:20 by macarval          #+#    #+#             */
/*   Updated: 2026/04/23 16:17:56 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

/// @brief Displays the currently allocated memory blocks in a human-readable
/// format, including the start and end addresses, size, and status (allocated
/// or free) of each block, as well as a total count of allocated bytes.
/// @param blocks A pointer to the first block in the zone to be displayed.
/// @return The total size of allocated blocks in the zone.
static int	print_blocks(t_block *blocks)
{
	t_block	*current;
	int		total_size;

	total_size = 0;
	current = blocks;
	while (current)
	{
		if (!is_free(current))
		{
			ft_printf("%p - %p : %u bytes\n",
				(void *)(current + 1),
				(void *)((char *)(current + 1) + get_real_size(current)),
				(unsigned int)get_real_size(current));
			total_size += get_real_size(current);
		}
		current = current->next;
	}
	return (total_size);
}

/// @brief Displays the currently allocated memory blocks in a human-readable
/// format, including the start and end addresses, size, and status (allocated
/// or free) of each block, as well as a total count of allocated bytes.
/// Additionally, it prints a hexdump of the first 16 bytes of allocated
/// blocks for debugging purposes.
/// @param zone A pointer to the first block in the zone to be displayed.
/// @param zone_name The name of the zone being displayed
/// (e.g., "TINY", "SMALL", "LARGE").
/// @return The total size of allocated blocks in the zone.
static int	print_zones(t_zone *zone, char *zone_name)
{
	int	total_size;

	total_size = 0;
	while (zone)
	{
		ft_printf("\n%s : %p\n", zone_name, (void *)zone);
		total_size += print_blocks(zone->blocks);
		zone = zone->next;
	}
	return (total_size);
}

/// @brief Displays the currently allocated memory blocks in a human-readable
/// format, including the start and end addresses, size, and status (allocated
/// or free) of each block, as well as a total count of allocated bytes.
// Additionally, it prints a hexdump of the first 16 bytes of allocated
/// blocks for debugging purposes.
/// @param void No parameters.
void	show_alloc_mem(void)
{
	int	total_size;

	total_size = 0;
	pthread_mutex_lock(&g_malloc.mutex);
	total_size += print_zones(g_malloc.tiny, "TINY");
	total_size += print_zones(g_malloc.small, "SMALL");
	if (g_malloc.large)
	{
		ft_printf("\nLARGE : %p\n", (void *)g_malloc.large);
		total_size += print_blocks(g_malloc.large);
	}
	ft_printf("\nTotal : %d bytes\n", total_size);
	pthread_mutex_unlock(&g_malloc.mutex);
}
