/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 13:38:28 by macarval          #+#    #+#             */
/*   Updated: 2026/04/17 20:45:28 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

/// @brief Finds a free block of memory that can accommodate the requested size
/// by traversing the appropriate zone's linked list of blocks.
/// @param size The requested original size.
/// @return A pointer to the found free block, or NULL if no suitable block
/// is found.
t_block	*find_free_block(size_t size)
{
	t_block	*current;

	current = get_zone(size);
	while (current)
	{
		if (current->status == FREE && current->size >= size)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/// @brief Finds the block corresponding to the given pointer by traversing
/// all zones and their blocks.
/// @param ptr The pointer to the block to find.
/// @return A pointer to the found block, or NULL if not found.
t_block	*find_real_block(void *ptr)
{
	t_block	*block;

	if (!ptr)
		return (NULL);
	block = find_block_from_ptr(g_malloc.tiny, ptr);
	if (block)
		return (block);
	block = find_block_from_ptr(g_malloc.small, ptr);
	if (block)
		return (block);
	block = find_block(g_malloc.large, ptr);
	if (block)
		return (block);
	return (NULL);
}

/// @brief Finds the block corresponding to the given pointer within a specific
/// zone by traversing its linked list of blocks.
/// @param zone The zone to search within.
/// @param ptr The pointer to the block to find.
/// @return A pointer to the found block, or NULL if not found.
t_block	*find_block_from_ptr(t_zone *zone, void *ptr)
{
	t_block	*block;

	while (zone)
	{
		block = find_block(zone->blocks, ptr);
		if (block)
			return (block);
		zone = zone->next;
	}
	return (NULL);
}

/// @brief Finds the block corresponding to the given pointer by traversing a
/// linked list of blocks.
/// @param block The head of the linked list to search.
/// @param ptr The pointer to the block to find.
/// @return A pointer to the found block, or NULL if not found.
t_block	*find_block(t_block *block, void *ptr)
{
	if (!block || !ptr)
		return (NULL);
	while (block)
	{
		if ((void *)(block + 1) == ptr)
			return (block);
		block = block->next;
	}
	return (NULL);
}
