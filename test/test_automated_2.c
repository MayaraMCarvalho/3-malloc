/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_automated_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:06:29 by macarval          #+#    #+#             */
/*   Updated: 2026/04/17 19:07:10 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

int	test_6(void)
{
	void	*arr[100];
	int		i;
	int		j;

	i = -1;
	while (++i < 10)
	{
		j = 0;
		while (j < 100)
		{
			arr[j] = malloc(128);
			if (!arr[j])
				return (1);
			j++;
		}
		j = 0;
		while (j < 100)
		{
			free(arr[j]);
			j++;
		}
	}
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
