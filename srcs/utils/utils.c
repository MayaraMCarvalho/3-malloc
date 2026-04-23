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
