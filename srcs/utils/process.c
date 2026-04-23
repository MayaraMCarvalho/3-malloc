/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:24:48 by macarval          #+#    #+#             */
/*   Updated: 2026/04/23 15:56:57 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

/// @brief Processes the freeing of a memory block, handling large blocks
/// separately and coalescing adjacent free blocks.
/// @param ptr The pointer to the memory block to be freed.
void	process_free(void *ptr)
{
	t_block	*block;
	t_zone	*zone;

	if (!ptr)
		return ;
	if (find_block(g_malloc.large, ptr))
	{
		free_large_block((t_block *)ptr - 1);
		return ;
	}
	block = find_real_block(ptr);
	if (!block || is_free(block) || get_real_size(block) == 0)
	{
		if (g_malloc.debug_mode)
			print_debug("free failed: invalid or already freed block.", ptr);
		return ;
	}
	set_free(block);
	zone = get_zone_of_block(block);
	if (!zone)
		return ;
	coalesce_zone(zone);
	handle_zone_empty(zone, zone->blocks);
	if (g_malloc.debug_mode)
		print_debug("free completed successfully!", ptr);
}

/// @brief Gets the system memory limit.
/// @return The system memory limit.
static size_t	get_system_limit(void)
{
	struct rlimit	rpl;
	static size_t	limit = 0;

	if (limit == 0)
	{
		if (getrlimit(RLIMIT_AS, &rpl) == 0
			&& rpl.rlim_cur != (rlim_t)RLIM_INFINITY)
			limit = rpl.rlim_cur;
		else
			limit = (size_t) - 1;
	}
	return (limit);
}

/// @brief Allocates memory using the custom memory allocation logic.
/// @param size The amount of memory to allocate.
/// @return A pointer to the allocated memory, or NULL if allocation fails.
void	*process_malloc(size_t size)
{
	size_t			aligned_size;
	void			*ptr;

	if (size == 0)
	{
		if (g_malloc.debug_mode)
			print_debug("malloc failed: size is 0.", NULL);
		return (NULL);
	}
	aligned_size = align_size(size);
	if (aligned_size > get_system_limit())
	{
		if (g_malloc.debug_mode)
			print_debug("malloc failed: size is greater than limit.", NULL);
		return (NULL);
	}
	ptr = allocate_block(aligned_size);
	if (g_malloc.debug_mode)
		print_debug("malloc completed successfully!", ptr);
	return (ptr);
}

/// @brief Reallocates memory using the custom memory allocation logic.
/// @param ptr A pointer to the memory block to be reallocated.
/// @param size The amount of memory to reallocate.
/// @return A pointer to the reallocated memory, or NULL if allocation fails.
void	*process_realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*new_ptr;
	size_t	aligned;

	block = find_real_block(ptr);
	if (!block || is_free(block))
		return (NULL);
	aligned = align_size(size);
	if (aligned <= get_real_size(block))
		return (shrink_block(block, aligned, ptr));
	if (expand_block(block, aligned))
		return (ptr);
	new_ptr = process_malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, get_real_size(block));
	process_free(ptr);
	return (new_ptr);
}
