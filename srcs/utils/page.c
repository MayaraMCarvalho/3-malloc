/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:19:35 by macarval          #+#    #+#             */
/*   Updated: 2026/04/23 15:34:02 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

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
