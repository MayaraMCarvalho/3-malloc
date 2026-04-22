/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:23:28 by macarval          #+#    #+#             */
/*   Updated: 2025/10/21 11:48:16 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

/// @brief Frees a block of memory.
/// @param ptr A pointer to the memory block to be freed.
void	free(void *ptr)
{
	t_block	*block;

	if (!ptr)
		return ;
	if (find_block(g_malloc.large, ptr))
	{
		free_large_block((t_block *)ptr - 1);
		return ;
	}
	block = find_real_block(ptr);
	if (!block || block->status == FREE || block->size == 0)
		return ;
	block->status = FREE;
	block = coalesce_blocks(block);
	handle_zone_empty(block);
}
