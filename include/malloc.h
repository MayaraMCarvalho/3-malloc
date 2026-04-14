/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:05:57 by macarval          #+#    #+#             */
/*   Updated: 2026/04/10 18:42:08 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
#include <sys/mman.h>
# include <pthread.h>

# define EXPORT __attribute__((visibility("default")))

// Prototypes
EXPORT void	free(void *ptr);
EXPORT void	*malloc(size_t size);
EXPORT void	*realloc(void *ptr, size_t size);
EXPORT void	show_alloc_mem(void);
EXPORT void	show_alloc_mem_ex(void);

#endif
