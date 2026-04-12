/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:51:50 by macarval          #+#    #+#             */
/*   Updated: 2026/04/12 13:51:38 by macarval         ###   ########.fr       */
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



