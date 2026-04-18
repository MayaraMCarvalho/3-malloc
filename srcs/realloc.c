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
	size_t	aligned;

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
	aligned = align_size(size);
	if (aligned <= block->size)
		return (shirink_block(block, aligned, ptr));
	if (expand_block(block, aligned))
		return (ptr);
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, block->size);
	free(ptr);
	return (new_ptr);
}
