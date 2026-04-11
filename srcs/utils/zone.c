/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:51:57 by macarval          #+#    #+#             */
/*   Updated: 2026/04/11 17:55:18 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

/// @brief Retrieves the appropriate zone (tiny, small, or large) based on the
/// requested size.
/// @param size The requested original size.
/// @return A pointer to the appropriate zone, or NULL if no suitable zone
/// is found.
t_block	*get_zone(size_t size)
{
	if (size <= TINY_MAX_SIZE)
	{
		if (g_malloc.tiny)
			return (g_malloc.tiny->blocks);
		return (NULL);
	}
	else if (size <= SMALL_MAX_SIZE)
	{
		if (g_malloc.small)
			return (g_malloc.small->blocks);
		return (NULL);
	}

	return (g_malloc.large);
}

/// @brief Creates a new memory zone of the specified size and initializes
/// its metadata.
/// @param zone_size The total size of the zone to be created.
/// @return A pointer to the newly created zone, or NULL if creation fails.
t_zone	*create_zone(size_t zone_size, t_zone **head)
{
	t_zone	*zone;

	zone = (t_zone *) mmap(NULL, zone_size, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (zone == MAP_FAILED)
		return (NULL);

	zone->total_size = zone_size;
	zone->next = NULL;

	zone->blocks = (t_block *)(zone + 1);

    // O tamanho disponível para o primeiro bloco é:
    // Total da zona - tamanho da struct zone - tamanho da struct block
    zone->blocks->size = zone_size - sizeof(t_zone) - sizeof(t_block);
    zone->blocks->status = FREE;
    zone->blocks->next = NULL;
    zone->blocks->prev = NULL;

	// zone->blocks = create_block(zone, zone_size - sizeof(t_zone));
	// if (!zone->blocks)
	// {
	// 	munmap(zone, zone_size);
	// 	return (NULL);
	// }

	add_zone(zone, head);
	return (zone);
}

void	add_zone(t_zone *zone, t_zone **head)
{
	t_zone	*current;

	if (!head)
		return ;

	if (!*head)
	{
		*head = zone;
		return ;
	}

	current = *head;
	while (current->next)
		current = current->next;

	current->next = zone;
}

t_block	*create_large_block(size_t size)
{
	t_block	*block;

	block = mmap(NULL, size + sizeof(t_block), PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (block == MAP_FAILED)
		return (NULL);

	block->size = size;
	block->status = ALLOCATED;
	block->next = NULL;
	block->prev = NULL;

	return (block);
}
