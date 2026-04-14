/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:51:57 by macarval          #+#    #+#             */
/*   Updated: 2026/04/14 20:02:30 by macarval         ###   ########.fr       */
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
	zone->prev = NULL;
	zone->next = NULL;
	zone->blocks = (t_block *)(zone + 1);
	zone->blocks->size = zone_size - sizeof(t_zone) - sizeof(t_block);
	zone->blocks->status = FREE;
	zone->blocks->prev = NULL;
	zone->blocks->next = NULL;
	add_zone(zone, head);
	return (zone);
}

/// @brief Adds a new zone to the end of the linked list of zones.
/// @param zone The zone to be added.
/// @param head A pointer to the head of the linked list of zones.
void	add_zone(t_zone *zone, t_zone **head)
{
	t_zone	*current;

	if (!head)
		return ;
	if (!*head)
	{
		*head = zone;
		zone->prev = NULL;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = zone;
	zone->prev = current;
}

void	handle_zone_empty(t_block *block)
{
	t_zone	*zone;

	if (block->prev == NULL && block->next == NULL && block->status == FREE)
	{
		zone = (t_zone *)((char *)block - sizeof(t_zone));
		if (zone == g_malloc.tiny && zone->next == NULL)
			return ;
		if (zone == g_malloc.small && zone->next == NULL)
			return ;
		if (zone->prev)
			zone->prev->next = zone->next;
		if (zone->next)
			zone->next->prev = zone->prev;
		if (zone == g_malloc.tiny)
			g_malloc.tiny = zone->next;
		else if (zone == g_malloc.small)
			g_malloc.small = zone->next;
		munmap((void *)zone, zone->total_size);
	}
}
