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
	size_t	alignment;

	alignment = 16;
	if (size % alignment == 0)
		return (size);
	return (((size / alignment) + 1) * alignment);
}

#ifdef __APPLE__

static size_t	get_page_size(void)
{
	return (getpagesize());
}

#else

static size_t	get_page_size(void)
{
	return (sysconf(_SC_PAGESIZE));
}

#endif

/// @brief Requests a new block of memory from the system by creating a new zone
/// for tiny or small sizes, or a large block for larger sizes.
/// @param size The requested original size.
/// @return A pointer to the newly allocated block, or NULL if allocation fails.
t_block	*request_space(size_t size)
{
	t_zone	*zone;
	t_block	*block;

	if (size <= TINY_MAX_SIZE)
		zone = create_zone(TINY_ZONE * get_page_size(), &g_malloc.tiny);
	else if (size <= SMALL_MAX_SIZE)
		zone = create_zone(SMALL_ZONE * get_page_size(), &g_malloc.small);
	else
		return (create_large_block(size));
	if (!zone)
		return (NULL);
	block = zone->blocks;
	return ((void *)(block));
}
