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

# include <unistd.h>

# include "malloc.h"
# include "libft.h"
# include "colors.h"

# define FREE			0
# define ALLOCATED		1
# define TINY_MAX_SIZE	128
# define SMALL_MAX_SIZE	1024
# define TINY_ZONE		4
# define SMALL_ZONE		26

typedef struct s_block
{
	size_t			size;
	int				status;
	struct s_block	*prev;
	struct s_block	*next;
}	t_block;

typedef struct s_zone
{
	t_block			*blocks;
	size_t			total_size;
	struct s_zone	*prev;
	struct s_zone	*next;
}	t_zone;

typedef struct s_malloc
{
	t_zone			*tiny;
	t_zone			*small;
	t_block			*large;
	pthread_mutex_t	mutex;
	int				debug_mode;
}	t_malloc;

extern t_malloc	g_malloc;

// block.c
void	*allocate_block(size_t size);
void	split_block(t_block *block, size_t size);
t_block	*coalesce_blocks(t_block *block);
void	*shrink_block(t_block *block, size_t aligned, void *ptr);
int		expand_block(t_block *block, size_t aligned);

// find_block.c
t_block	*find_free_block(size_t size);
t_block	*find_real_block(void *ptr);
t_block	*find_block_from_ptr(t_zone *zone, void *ptr);
t_block	*find_block(t_block *block, void *ptr);

// large_block.c
t_block	*create_large_block(size_t size);
void	add_large_block(t_block *block);
void	free_large_block(t_block *block);

// page.c
t_block	*request_space(size_t size);

// zone.c
t_block	*get_zone(size_t size);
t_zone	*create_zone(size_t zone_size, t_zone **head);
void	add_zone(t_zone *zone, t_zone **head);
void	handle_zone_empty(t_block *block);

// utils.c
size_t	align_size(size_t size);
void	process_free(void *ptr);
void	*process_malloc(size_t size);
void	*process_realloc(void *ptr, size_t size);
void	print_debug(char *message, void *ptr);

#endif
