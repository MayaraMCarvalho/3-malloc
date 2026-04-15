/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:30:01 by macarval          #+#    #+#             */
/*   Updated: 2026/04/14 21:22:38 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "colors.h"

void	welcome(void);
void	goodbye(void);

static void	tiny_tests(void)
{
	char	*t1;
	char	*t2;
	char	*t3;

	ft_printf("%s\n*** Test TINY ***%s\n", YELLOW, RESET);
	t1 = malloc(12);
	t2 = malloc(5);
	t3 = malloc(128);
	t1[0] = 'A';
	t2[0] = 'B';
	t3[0] = 'C';
	ft_printf(CYAN "=== Before Free ===" RESET);
	show_alloc_mem();
	show_alloc_mem_ex();
	free(t1);
	free(t2);
	free(t3);
	ft_printf(CYAN "\n=== After Free ===" RESET);
	show_alloc_mem_ex();
}

static void	small_tests(void)
{
	char	*s1;
	char	*s2;
	char	*s3;

	ft_printf("%s\n*** Test SMALL ***%s\n", YELLOW, RESET);
	s1 = malloc(129);
	s2 = malloc(523);
	s3 = malloc(1024);
	s1[0] = 'E';
	s2[0] = 'F';
	s3[0] = 'G';
	ft_printf(CYAN "=== Before Free ===" RESET);
	show_alloc_mem();
	show_alloc_mem_ex();
	free(s1);
	free(s2);
	free(s3);
	ft_printf(CYAN "\n=== After Free ===" RESET);
	show_alloc_mem_ex();
}

static void	large_tests(void)
{
	char	*l1;
	char	*l2;
	char	*l3;

	ft_printf("%s\n*** Test LARGE ***%s\n", YELLOW, RESET);
	l1 = malloc(1025);
	l2 = malloc(1088);
	l3 = malloc(2050);
	ft_printf(CYAN "=== Before Free ===" RESET);
	show_alloc_mem();
	show_alloc_mem_ex();
	free(l1);
	free(l2);
	free(l3);
	ft_printf(CYAN "\n=== After Free ===" RESET);
	show_alloc_mem_ex();
}

static void	test_malloc_free(void)
{
	char	*str;

	ft_printf("%s\n*** Test Malloc and Free ***%s\n", YELLOW, RESET);
	str = malloc(15 * sizeof(char));
	if (!str)
		ft_printf("%sError: Test 1.1%s\n", RED, RESET);
	ft_strlcpy(str, "Hello Malloc!", 13);
	ft_printf("str: %s\n\n", str);
	if (ft_strncmp(str, "Hello Malloc!", 14) != 0)
		ft_printf("%sError: Test 1.2%s\n", RED, RESET);
	ft_printf(CYAN "=== Before Free ===" RESET);
	show_alloc_mem();
	show_alloc_mem_ex();
	free(str);
	ft_printf(CYAN "\n=== After Free ===" RESET);
	show_alloc_mem_ex();
}

static void	test_realloc(void)
{
	char	*str;

	ft_printf("%s\n*** Test REALLOC ***%s\n", YELLOW, RESET);
	str = malloc(5);
	ft_strlcpy(str, "Hello", 6);
	ft_printf("str: %s\n", str);
	ft_printf("Before Realloc: %s\n", str);
	show_alloc_mem_ex();
	str = realloc(str, 20);
	ft_strlcat(str, " World, it worked!", 24);
	ft_printf("After Realloc: %s\n", str);
	show_alloc_mem_ex();
	free(str);
}

int	main(void)
{
	welcome();
	tiny_tests();
	small_tests();
	large_tests();
	test_malloc_free();
	test_realloc();
	goodbye();
	return (0);
}
