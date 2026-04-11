/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:51:57 by macarval          #+#    #+#             */
/*   Updated: 2026/04/11 16:28:14 by macarval         ###   ########.fr       */
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

/// @brief Requests a new block of memory from the system by creating a new zone
/// for tiny or small sizes, or a large block for larger sizes.
/// @param size The requested original size.
/// @return A pointer to the newly allocated block, or NULL if allocation fails.
t_block	*request_space(size_t size)
{
	t_zone	*zone;
	t_block	*block;

	if (size <= TINY_MAX_SIZE)
		zone = create_zone(TINY_ZONE);
	else if (size <= SMALL_MAX_SIZE)
		zone = create_zone(SMALL_ZONE);
	else
		return (create_large_block(size));

	if (!zone)
		return (NULL);

	block = zone->blocks;
	while (block->next)
		block = block->next;

	block->next = create_block(zone, size);
	if (!block->next)
		return (NULL);

	return (block->next);
}

/// @brief Creates a new memory zone of the specified size and initializes
/// its metadata.
/// @param zone_size The total size of the zone to be created.
/// @return A pointer to the newly created zone, or NULL if creation fails.
t_zone	*create_zone(size_t zone_size)
{
	t_zone	*zone;

	zone = (t_zone *) mmap(NULL, zone_size, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (zone == MAP_FAILED)
		return (NULL);

	zone->total_size = zone_size;
	zone->next = NULL;

	zone->blocks = create_block(zone, zone_size - sizeof(t_zone));
	if (!zone->blocks)
	{
		munmap(zone, zone_size);
		return (NULL);
	}

	add_zone(zone, zone_size);
	return (zone);
}

void	add_zone(t_zone *zone, size_t zone_size)
{
	t_zone	*current;
	t_zone	**head;

	if (zone_size == TINY_ZONE)
		head = &g_malloc.tiny;

	if (zone_size == SMALL_ZONE)
		head = g_malloc.small;

	if (!*head)
		return (*head = zone);

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
