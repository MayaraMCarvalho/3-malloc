/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_2_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:06:29 by macarval          #+#    #+#             */
/*   Updated: 2026/04/17 18:43:16 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "colors.h"

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

int	test_7_tiny(void)
{
	char	*t1;
	char	*t2;
	char	*t3;

	t1 = malloc(12);
	t2 = malloc(5);
	t3 = malloc(128);
	ft_printf("\n%s*** Test TINY ***%s\n", YELLOW, RESET);
	t1[0] = 'A';
	t2[0] = 'B';
	t3[0] = 'C';
	show_alloc_mem_ex();
	free(t1);
	free(t2);
	free(t3);
	ft_printf("%s\n=== After Free ===\n%s", CYAN, RESET);
	show_alloc_mem_ex();
	return (0);
}

int	test_8_small(void)
{
	char	*s1;
	char	*s2;
	char	*s3;

	s1 = malloc(129);
	s2 = malloc(523);
	s3 = malloc(1024);
	ft_printf("\n%s*** Test SMALL ***%s\n", YELLOW, RESET);
	s1[0] = 'E';
	s2[0] = 'F';
	s3[0] = 'G';
	show_alloc_mem_ex();
	free(s1);
	free(s2);
	free(s3);
	ft_printf("%s\n=== After Free ===\n%s", CYAN, RESET);
	show_alloc_mem_ex();
	return (0);
}

int	test_9_large(void)
{
	char	*l1;
	char	*l2;
	char	*l3;

	l1 = malloc(1025);
	l2 = malloc(1088);
	l3 = malloc(2050);
	ft_printf("\n%s*** Test LARGE ***%s\n", YELLOW, RESET);
	show_alloc_mem_ex();
	free(l1);
	free(l2);
	free(l3);
	ft_printf("%s\n=== After Free ===\n%s", CYAN, RESET);
	show_alloc_mem_ex();
	return (0);
}

int	test_10_edge_cases(void)
{
	void	*ptr1;
	void	*ptr2;

	ft_printf("\n%s*** EXTREME CASE TEST ***%s\n", YELLOW, RESET);
	ft_printf("[1] malloc(0)...\n");
	ptr1 = malloc(0);
	if (ptr1)
		return (1);
	ft_printf("[2] free(NULL)...\n");
	free(NULL);
	ft_printf("[3] realloc(NULL, 42)...\n");
	ptr2 = realloc(NULL, 42);
	ft_printf("[4] realloc(ptr, 0)...\n");
	ptr2 = realloc(ptr2, 0);
	ft_printf("[5] free(invalid_pointer)...\n");
	free((void *)0xDEADBEEF);
	ft_printf("%s-> Extreme cases survived without Segfault!%s\n",
		GREEN, RESET);
	return (0);
}
