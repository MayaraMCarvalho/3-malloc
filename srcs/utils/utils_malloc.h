/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_malloc.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:33:03 by macarval          #+#    #+#             */
/*   Updated: 2026/04/11 16:33:03 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_MALLOC_H
# define UTILS_MALLOC_H

# include "malloc.h"
# include "libft.h"
# include "colors.h"

# ifdef __APPLE__
	# define PAGE_SIZE getpagesize()
# else
	# define PAGE_SIZE sysconf(_SC_PAGESIZE)
# endif

# define FREE			0
# define ALLOCATED		1
# define TINY_MAX_SIZE	128
# define SMALL_MAX_SIZE	1024
# define TINY_ZONE		(4 * PAGE_SIZE)
# define SMALL_ZONE		(26 * PAGE_SIZE)

typedef struct s_block
{
	size_t			size;
	int				status;
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

extern t_malloc	g_malloc;

// block.c
size_t	align_size(size_t size);
void	*allocate_block(size_t size);
t_block	*find_free_block(size_t size);
t_block	*create_block(t_zone *zone, size_t size);

// zone.c
t_block	*get_zone(size_t size);
t_block	*request_space(size_t size);
t_zone	*create_zone(size_t zone_size);
t_block	*create_large_block(size_t size);
void	add_zone(t_zone *zone);

// utils.c
int		initialize_malloc(void);


#endif
