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

t_malloc	g_malloc = {
	NULL,
	NULL,
	NULL,
	PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP,
	0
};

/// @brief Allocates memory using the standard malloc function if the debug
/// mode is enabled, otherwise uses the custom memory allocation logic.
/// @param size The amount of memory to allocate.
/// @return A pointer to the allocated memory, or NULL if allocation fails.
void	*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_malloc.mutex);
	ptr = process_malloc(size);
	pthread_mutex_unlock(&g_malloc.mutex);
	return (ptr);
}
