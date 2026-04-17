/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_3_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:06:29 by macarval          #+#    #+#             */
/*   Updated: 2026/04/17 18:34:37 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "colors.h"

int	test_11_fragmentation(void)
{
	void	*a;
	void	*b;
	void	*c;

	a = malloc(128);
	b = malloc(128);
	c = malloc(128);
	ft_printf("\n%s*** FRAGMENTATION AND COALESCING TEST ***%s\n",
		YELLOW, RESET);
	ft_printf("-> 3 blocks allocated. Freeing the ends (A and C)...\n");
	free(a);
	free(c);
	ft_printf("-> Freeing the middle (B). Should form a single block.\n");
	free(b);
	show_alloc_mem_ex();
	return (0);
}

int	test_12_overlap(void)
{
	char	*a;
	char	*b;
	size_t	diff;

	a = malloc(16);
	b = malloc(16);
	diff = (size_t)b - (size_t)a;
	ft_printf("\n%s*** OVERLAP TEST ***%s\n", YELLOW, RESET);
	ft_printf("-> diff: %zu\n", diff);
	if (diff < 16)
		return (1);
	return (0);
}

int	test_13_massive(void)
{
	void	*ptr;
	void	*l1;
	void	*l2;

	ptr = malloc((size_t)1024 * 1024 * 1024 * 2);
	if (ptr)
		free(ptr);
	l1 = malloc(100000);
	l2 = malloc(200000);
	if (!l1 || !l2)
		return (1);
	free(l1);
	free(l2);
	return (0);
}

int	test_14_shrink_coalesce(void)
{
	void	*a;
	void	*b;
	void	*c;
	void	*test_block;

	a = malloc(32);
	b = malloc(32);
	c = malloc(32);
	if (!a || !b || !c)
		return (1);
	free(b);
	a = realloc(a, 16);
	test_block = malloc(40);
	if (!test_block)
		return (1);
	free(a);
	free(c);
	free(test_block);
	return (0);
}

int	test_15_expand_inplace(void)
{
	void	*a;
	void	*b;
	void	*c;
	void	*a_old_addr;

	a = malloc(16);
	b = malloc(32);
	c = malloc(16);
	a_old_addr = a;
	if (!a || !b || !c)
		return (1);
	free(b);
	a = realloc(a, 32);
	if (a != a_old_addr)
		return (1);
	free(a);
	free(c);
	return (0);
}
