/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 20:08:33 by macarval          #+#    #+#             */
/*   Updated: 2026/04/17 20:48:08 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

/// @brief Creates a new large block of memory.
/// @param size The size of the memory block to be allocated.
/// @return A pointer to the newly allocated block, or NULL if allocation fails.
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
	add_large_block(block);
	return (block);
}

/// @brief Adds a large block to the linked list of large blocks.
/// @param block The block to be added.
void	add_large_block(t_block *block)
{
	if (!g_malloc.large)
	{
		g_malloc.large = block;
		return ;
	}
	block->next = g_malloc.large;
	g_malloc.large->prev = block;
	g_malloc.large = block;
}

/// @brief Frees a large block of memory.
/// @param block The block to be freed.
void	free_large_block(t_block *block)
{
	if (!block)
		return ;
	if (block->prev)
		block->prev->next = block->next;
	if (block->next)
		block->next->prev = block->prev;
	if (block->prev == NULL)
		g_malloc.large = block->next;
	munmap((void *)block, block->size + sizeof(t_block));
}
