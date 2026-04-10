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

#include <stdlib.h>
#include <pthread.h>

#include "libft.h"
#include "colors.h"

// free.c
void	free(void *ptr);

// malloc.c
void	*malloc(size_t size);

// relloc.c
void	*realloc(void *ptr, size_t size);

// show_alloc_mem.c
void	show_alloc_mem(void);

// utils.c

// test/info.c
void    welcome(void);
void    goodbye(void);


#endif
