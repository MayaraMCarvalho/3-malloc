/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:23:31 by macarval          #+#    #+#             */
/*   Updated: 2025/10/21 11:43:46 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

/// @brief Aligns the size to the next multiple of 16 bytes (64-bit).
/// @param size The requested original size.
/// @return The aligned size.
size_t	align_size(size_t size)
{
	return ((size + 15) & ~15);
}

/// @brief Processes the freeing of a memory block, handling large blocks
/// separately and coalescing adjacent free blocks.
/// @param ptr The pointer to the memory block to be freed.
void	process_free(void *ptr)
{
	t_block	*block;

	if (!ptr)
		return ;
	if (find_block(g_malloc.large, ptr))
	{
		free_large_block((t_block *)ptr - 1);
		if (g_malloc.debug_mode)
			print_debug("free completed successfully! (Large)", ptr);
		return ;
	}
	block = find_real_block(ptr);
	if (!block || block->status == FREE || block->size == 0)
	{
		if (g_malloc.debug_mode)
			print_debug("free failed: invalid or already freed block.", ptr);
		return ;
	}
	block->status = FREE;
	block = coalesce_blocks(block);
	handle_zone_empty(block);
	if (g_malloc.debug_mode)
		print_debug("free completed successfully!", ptr);
}

/// @brief Allocates memory using the custom memory allocation logic.
/// @param size The amount of memory to allocate.
/// @return A pointer to the allocated memory, or NULL if allocation fails.
void	*process_malloc(size_t size)
{
	size_t			aligned_size;
	struct rlimit	limit;
	void			*ptr;

	if (size == 0)
	{
		if (g_malloc.debug_mode)
			print_debug("malloc failed: size is 0.", NULL);
		return (NULL);
	}
	aligned_size = align_size(size);
	if (getrlimit(RLIMIT_AS, &limit) == 0
		&& limit.rlim_cur != RLIM_INFINITY && aligned_size > limit.rlim_cur)
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

void	*process_realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*new_ptr;
	size_t	aligned;

	block = find_real_block(ptr);
	if (!block || block->status == FREE)
		return (NULL);
	aligned = align_size(size);
	if (aligned <= block->size)
		return (shrink_block(block, aligned, ptr));
	if (expand_block(block, aligned))
		return (ptr);
	new_ptr = process_malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, block->size);
	process_free(ptr);
	return (new_ptr);
}

/// @brief Prints a debug message with the given message and pointer.
/// @param message The message to print.
/// @param ptr The pointer to print.
void	print_debug(char *message, void *ptr)
{
	if (!g_malloc.debug_mode)
		return ;
	ft_printf("\n%s", GREEN);
	if (ptr)
		ft_printf("[DEBUG] %s: %p", message, ptr);
	else
		ft_printf("[DEBUG] %s", message);
	ft_printf("%s\n", RESET);
}
