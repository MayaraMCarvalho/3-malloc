/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 20:08:33 by macarval          #+#    #+#             */
/*   Updated: 2026/04/23 14:31:09 by macarval         ###   ########.fr       */
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
	set_allocated(block);
	block->next = NULL;
	add_large_block(block);
	return (block);
}

/// @brief Adds a large block to the linked list of large blocks.
/// @param block The block to be added.
void	add_large_block(t_block *block)
{
	block->next = g_malloc.large;
	g_malloc.large = block;
}

/// @brief Frees a large block of memory.
/// @param block The block to be freed.
void	free_large_block(t_block *block)
{
	t_block	*tmp;

	if (!block)
		return ;
	if (g_malloc.large == block)
		g_malloc.large = block->next;
	else
	{
		tmp = g_malloc.large;
		while (tmp && tmp->next != block)
			tmp = tmp->next;
		if (tmp)
			tmp->next = block->next;
	}
	munmap((void *)block, get_real_size(block) + sizeof(t_block));
	if (g_malloc.debug_mode)
		print_debug("free completed successfully! (Large)", (void *)block
			+ sizeof(t_block));
}
