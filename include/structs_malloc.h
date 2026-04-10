/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_malloc.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:05:57 by macarval          #+#    #+#             */
/*   Updated: 2025/10/17 20:29:20 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_MALLOC_H
# define STRUCTS_MALLOC_H

# include "malloc.h"
# include "libft.h"

# ifdef __APPLE__
	#  define PAGE_SIZE getpagesize()
# else
	#  define PAGE_SIZE sysconf(_SC_PAGESIZE)
# endif

#define TINY_MAX_SIZE	128
#define SMALL_MAX_SIZE	1024
#define TINY_ZONE		(4 * PAGE_SIZE)
#define SMALL_ZONE		(26 * PAGE_SIZE)

typedef struct s_block
{
	size_t			size;
	int				status; // 0 = free, 1 = allocated
	struct s_block	*next;
	struct s_block	*prev;
}	t_block;

typedef struct s_zone
{
	t_block			*blocks;
	size_t			total_size;
	struct s_zone	*next;
}	t_zone;

typedef struct s_malloc
{
	t_zone			*tiny;
	t_zone			*small;
	t_block			*large;
	pthread_mutex_t	mutex;
}	t_malloc;

extern t_malloc g_malloc;

#endif
