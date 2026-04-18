/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:51:50 by macarval          #+#    #+#             */
/*   Updated: 2026/04/17 21:06:52 by macarval         ###   ########.fr       */
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

/// @brief Splits a block into two if the remaining space after allocation is
/// large enough to hold another block, updating the linked list
/// pointers accordingly.
/// @param block The block to be split.
/// @param size The requested original size for the allocated block.
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

/// @brief Coalesces adjacent free blocks into a single larger block to reduce
/// fragmentation, updating the linked list pointers accordingly.
/// @param block The block to be coalesced with its adjacent free blocks.
/// @return A pointer to the resulting coalesced block.
t_block	*coalesce_blocks(t_block *block)
{
	if (block->next && block->next->status == FREE)
	{
		block->size += sizeof(t_block) + block->next->size;
		block->next = block->next->next;
		if (block->next)
			block->next->prev = block;
	}
	if (block->prev && block->prev->status == FREE)
	{
		block->prev->size += sizeof(t_block) + block->size;
		block->prev->next = block->next;
		if (block->next)
			block->next->prev = block->prev;
		block = block->prev;
	}
	return (block);
}

/// @brief Shrinks a block of memory.
/// @param block The block to be shirinked.
/// @param aligned The aligned size.
/// @param ptr The pointer to the memory block.
/// @return A pointer to the shirinked block.
void	*shrink_block(t_block *block, size_t aligned, void *ptr)
{
	split_block(block, aligned);
	if (block->next && block->next->status == FREE)
		coalesce_blocks(block->next);
	return (ptr);
}

/// @brief Expands a block of memory if the next block is free and large
/// enough to hold the additional data.
/// @param block The block to be expanded.
/// @param aligned The aligned size of the expanded block.
/// @return 1 if the block was expanded, 0 otherwise.
int	expand_block(t_block *block, size_t aligned)
{
	size_t	expand;

	if (!block->next || block->next->status == ALLOCATED)
		return (0);
	expand = block->size + sizeof(t_block) + block->next->size;
	if (expand < aligned)
		return (0);
	block->size += sizeof(t_block) + block->next->size;
	block->next = block->next->next;
	if (block->next)
		block->next->prev = block;
	split_block(block, aligned);
	return (1);
}
