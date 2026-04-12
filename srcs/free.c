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

void	free(void *ptr)
{
	if (ptr)
	{
		t_block	*block;

		block = (t_block *)ptr - 1;
		block->status = FREE;

		// Optionally, you can implement coalescing of adjacent free blocks here
	}

}
