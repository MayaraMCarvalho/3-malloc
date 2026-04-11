/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:23:34 by macarval          #+#    #+#             */
/*   Updated: 2025/10/21 11:48:08 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

t_malloc g_malloc = {NULL, NULL, NULL, PTHREAD_MUTEX_INITIALIZER};

/// @brief Allocates a block of memory of the specified size, first trying to
/// find a free block in the appropriate zone, and if none is found, requesting
/// new space from the system.
/// @param size The requested original size.
/// @return A pointer to the allocated block, or NULL if allocation fails.
void	*malloc(size_t size)
{
	size_t	aligned_size;

	if (size <= 0)
		return (NULL);

	// #include <unistd.h>
	// write(1, "Chegou na verificacao do bloco 2\n", 33);
	aligned_size = align_size(size);

	return (allocate_block(aligned_size));
}
