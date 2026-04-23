/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_automated_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:52:34 by macarval          #+#    #+#             */
/*   Updated: 2026/04/23 01:00:04 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include <pthread.h>
#include <string.h>

int	test_17_invalid_frees(void)
{
	int				stack_var;
	void			*heap_ptr;
	void *volatile	fake_ptr;

	stack_var = 42;
	heap_ptr = malloc(16);
	if (!heap_ptr)
		return (1);
	fake_ptr = &stack_var;
	free(fake_ptr);
	free((char *)heap_ptr + 1);
	free(heap_ptr);
	free(heap_ptr);
	return (0);
}

static void	*test_thread_hammer(void *arg)
{
	int		i;
	void	*ptrs[100];

	(void)arg;
	i = 0;
	while (i < 100)
	{
		ptrs[i] = malloc(128);
		i++;
	}
	i = 0;
	while (i < 100)
		free(ptrs[i++]);
	return (NULL);
}

int	test_18_thread_safety(void)
{
	pthread_t	threads[10];
	int			i;

	i = 0;
	while (i < 10)
	{
		if (pthread_create(&threads[i], NULL, test_thread_hammer, NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < 10)
		pthread_join(threads[i++], NULL);
	return (0);
}

int	test_19_realloc_large(void)
{
	char	*ptr;
	size_t	large_size;

	large_size = (size_t)1024 * 1024 * 2;
	ptr = malloc(large_size);
	if (!ptr)
		return (1);
	memset(ptr, 'X', large_size);
	ptr = realloc(ptr, large_size + 1024 * 1024);
	if (!ptr)
		return (1);
	if (ptr[0] != 'X' || ptr[large_size - 1] != 'X')
		return (1);
	free(ptr);
	return (0);
}
