/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:51:50 by macarval          #+#    #+#             */
/*   Updated: 2026/04/11 17:48:26 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

/// @brief Aligns the size to the next multiple of sizeof(size_t).
/// @param size The requested original size.
/// @return The aligned size.
/// @example If size is 10 and sizeof(size_t) is 8, the function will return 16.
size_t	align_size(size_t size)
{
	size_t	alignment;

	alignment = sizeof(size_t);
	if (size % alignment == 0)
		return (size);

	return (((size / alignment) + 1) * alignment);
}

/// @brief Allocates a block of memory of the specified size, first trying to
/// find a free block in the appropriate zone, and if none is found, requesting
/// new space from the system.
/// @param size The requested original size.
/// @return A pointer to the allocated block, or NULL if allocation fails.
void	*allocate_block(size_t size)
{
	t_block	*current;
	t_block	*new_block;

	current = find_free_block(size);
	if (current)
	{
		current->status = ALLOCATED;
		return (current + 1);
	}

	new_block = request_space(size);
	if (!new_block)
		return (NULL);

	new_block->size = size;
	new_block->status = ALLOCATED;

	return (new_block + 1);
}

/// @brief Finds a free block of memory that can accommodate the requested size
/// by traversing the appropriate zone's linked list of blocks.
/// @param size The requested original size.
/// @return A pointer to the found free block, or NULL if no suitable block
/// is found.
t_block	*find_free_block(size_t size)
{
	t_block	*current;
	int		type_zone;

	current = get_zone(size);
	while (current)
	{
		if (current->status == FREE && current->size >= size)
			return (current);
		current = current->next;
	}

	return (NULL);
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
		zone = create_zone(TINY_ZONE, &g_malloc.tiny);
	else if (size <= SMALL_MAX_SIZE)
		zone = create_zone(SMALL_ZONE, &g_malloc.small);
	else
		return (create_large_block(size));

	if (!zone)
		return (NULL);

	block = zone->blocks;

	return (block);
}

t_block	*create_block(t_zone *zone, size_t size)
{
	t_block	*block;

	block = (t_block *)((char *)zone + sizeof(t_zone));

	block->size = size;
	block->status = FREE;
	block->next = NULL;
	block->prev = NULL;

	return (block);
}
