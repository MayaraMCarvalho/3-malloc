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

/// @brief Reallocates memory using the custom memory allocation logic.
/// @param ptr A pointer to the memory block to be reallocated.
/// @param size The amount of memory to reallocate.
/// @return A pointer to the reallocated memory, or NULL if allocation fails.
void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	pthread_mutex_lock(&g_malloc.mutex);
	new_ptr = process_realloc(ptr, size);
	pthread_mutex_unlock(&g_malloc.mutex);
	return (new_ptr);
}
