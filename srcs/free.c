/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:23:28 by macarval          #+#    #+#             */
/*   Updated: 2025/10/21 11:48:16 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_malloc.h"

/// @brief Frees a block of memory using the standard free function if debug
/// mode is enabled, otherwise uses the custom memory freeing logic.
/// @param ptr A pointer to the memory block to be freed.
void	free(void *ptr)
{
	pthread_mutex_lock(&g_malloc.mutex);
	process_free(ptr);
	pthread_mutex_unlock(&g_malloc.mutex);
}
