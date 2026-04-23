/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 14:51:50 by macarval          #+#    #+#             */
/*   Updated: 2026/04/23 14:33:00 by macarval         ###   ########.fr       */
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
	set_allocated(block);
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
	size_t	real_size;

	real_size = get_real_size(block);
	if (real_size >= size + sizeof(t_block) + sizeof(size_t))
	{
		new_block = (t_block *)((char *)(block + 1) + size);
		new_block->size = real_size - size - sizeof(t_block);
		set_free(new_block);
		new_block->next = block->next;
		block->size = size | (block->size & 1);
		block->next = new_block;
	}
}

/// @brief Coalesces all adjacent free blocks into a single larger block to
/// reduce fragmentation, updating the linked list pointers accordingly.
/// @param zone The zone to be coalesced.
void	coalesce_zone(t_zone	*zone)
{
	t_block	*block;
	size_t	merged_size;

	if (!zone || !zone->blocks)
		return ;
	block = zone->blocks;
	while (block && block->next)
	{
		if (is_free(block) && is_free(block->next))
		{
			merged_size = get_real_size(block)
				+ sizeof(t_block) + get_real_size(block->next);
			block->size = merged_size;
			block->next = block->next->next;
		}
		else
			block = block->next;
	}
}

/// @brief Shrinks a block of memory.
/// @param block The block to be shirinked.
/// @param aligned The aligned size.
/// @param ptr The pointer to the memory block.
/// @return A pointer to the shirinked block.
void	*shrink_block(t_block *block, size_t aligned, void *ptr)
{
	t_zone	*zone;

	split_block(block, aligned);
	zone = get_zone_of_block(block);
	if (zone)
		coalesce_zone(zone);
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

	if (!block->next || !is_free(block->next))
		return (0);
	expand = get_real_size(block) + sizeof(t_block)
		+ get_real_size(block->next);
	if (expand < aligned)
		return (0);
	block->size = expand | (block->size & 1);
	block->next = block->next->next;
	split_block(block, aligned);
	return (1);
}
