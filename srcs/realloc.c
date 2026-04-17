/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:23:24 by macarval          #+#    #+#             */
/*   Updated: 2025/10/21 11:48:13 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	block = find_real_block(ptr);
	if (!block || block->status == FREE)
		return (NULL);
	if (align_size(size) <= block->size)
	{
		split_block(block, align_size(size));
		return (ptr);
	}
	if (block->next && block->next->status == FREE
		&& (block->size + sizeof(t_block) + block->next->size)
		>= align_size(size))
	{
		block->size += sizeof(t_block) + block->next->size;
		block->next = block->next->next;
		if (block->next)
			block->next->prev = block;
		split_block(block, align_size(size));
		return (ptr);
	}
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, block->size);
	free(ptr);
	return (new_ptr);
}
