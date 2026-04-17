/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_visual_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:05:34 by macarval          #+#    #+#             */
/*   Updated: 2026/04/17 19:56:10 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "colors.h"

int	test_14_shrink_coalesce(void)
{
	void	*a;
	void	*b;
	void	*c;

	a = malloc(128);
	b = malloc(128);
	c = malloc(128);
	if (!a || !b || !c)
		return (1);
	ft_printf("Three blocks (A, B, C) have been allocated. ");
	ft_printf("Freeing block B to create a hole...\n");
	free(b);
	show_alloc_mem_ex();
	ft_printf("Shrinking A (from 128 to 16 bytes).\n");
	ft_printf("A's remaining space should automatically merge ");
	ft_printf("with the hole B!\n");
	a = realloc(a, 16);
	show_alloc_mem_ex();
	free(a);
	free(c);
	return (0);
}
