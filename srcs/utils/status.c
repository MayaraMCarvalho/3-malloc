/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 10:28:39 by macarval          #+#    #+#             */
/*   Updated: 2026/04/23 11:21:19 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

/// @brief Gets the real size of a block.
/// @param block The block to get the real size of.
/// @return The real size of the block.
size_t	get_real_size(t_block *block)
{
	return (block->size & ~1);
}

/// @brief Checks if a block is free.
/// @param block The block to check.
/// @return 1 if the block is free, 0 otherwise.
int	is_free(t_block *block)
{
	return (!(block->size & 1));
}

/// @brief Sets a block as free.
/// @param block The block to set as free.
void	set_free(t_block *block)
{
	block->size &= ~1;
}

/// @brief Sets a block as allocated.
/// @param block The block to set as allocated.
void	set_allocated(t_block *block)
{
	block->size |= 1;
}
