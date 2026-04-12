/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:23:20 by macarval          #+#    #+#             */
/*   Updated: 2026/04/11 22:02:56 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

static int	print_blocks(t_block *blocks)
{
	t_block	*current;
	int		total_size;

	total_size = 0;
	current = blocks;
	while (current)
	{
		if (current->status == ALLOCATED)
		{
			ft_printf("%p - %p : %u bytes\n",
				(void *)(current + 1),
				(void *)((char *)(current + 1) + current->size),
				(unsigned int)current->size);
			total_size += current->size;
		}
		current = current->next;
	}
	return (total_size);
}

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

void	show_alloc_mem(void)
{
	int	total_size;

	total_size = 0;
	total_size += print_zones(g_malloc.tiny, "TINY");
	total_size += print_zones(g_malloc.small, "SMALL");

	if (g_malloc.large)
	{
		ft_printf("\nLARGE : %p\n", (void *)g_malloc.large);
		total_size += print_blocks(g_malloc.large);
	}
	ft_printf("\nTotal : %d bytes\n", total_size);
}
