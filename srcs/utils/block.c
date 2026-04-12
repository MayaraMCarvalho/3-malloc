/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:51:50 by macarval          #+#    #+#             */
/*   Updated: 2026/04/11 21:40:10 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

/// @brief Allocates a block of memory of the specified size, first trying to
/// find a free block in the appropriate zone, and if none is found, requesting
/// new space from the system.
/// @param size The requested original size.
/// @return A pointer to the allocated block, or NULL if allocation fails.
void	*allocate_block(size_t size)
{
	t_block	*block;

	block = find_free_block(size);
	if (!block)
	{
		block = request_space(size);
		if (!block)
			return (NULL);
	}

	split_block(block, size);
	block->status = ALLOCATED;

	return (block + 1);
}

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

void	split_block(t_block *block, size_t size)
{
	t_block	*new_block;

	if (block->size >= size + sizeof(t_block) + sizeof(size_t))
	{
		new_block = (t_block *)((char *)(block + 1) + size);
		new_block->size = block->size - size - sizeof(t_block);
		new_block->status = FREE;
		new_block->next = block->next;
		new_block->prev = block;

		if (new_block->next)
			new_block->next->prev = new_block;

		block->size = size;
		block->next = new_block;
	}
}
