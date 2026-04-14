/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:30:01 by macarval          #+#    #+#             */
/*   Updated: 2026/04/14 19:48:58 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "colors.h"

#include <string.h>

void	welcome(void);
void	goodbye(void);

static void	tiny_tests(void)
{
	char	*t1;
	char	*t2;
	char	*t3;
	char	*t4;

	ft_printf("%s\n*** Teste TINY ***%s\n", YELLOW, RESET);

	t1 = malloc(12);
	t2 = malloc(5);
	t3 = malloc(1);
	t4 = malloc(128);

	t1[0] = 'A';
	t2[0] = 'B';
	t3[0] = 'C';
	t4[0] = 'D';

	ft_printf(CYAN "=== Antes do Free ===" RESET);
	show_alloc_mem();
	show_alloc_mem_ex();

	free(t1);
	free(t2);
	free(t3);
	free(t4);

	ft_printf(CYAN "\n=== Depois do Free ===" RESET);
	show_alloc_mem_ex();
}

static void	small_tests(void)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;

	ft_printf("%s\n*** Teste SMALL ***%s\n", YELLOW, RESET);

	s1 = malloc(129);
	s2 = malloc(523);
	s3 = malloc(679);
	s4 = malloc(1024);

	s1[0] = 'E';
	s2[0] = 'F';
	s3[0] = 'G';
	s4[0] = 'H';

	ft_printf(CYAN "=== Antes do Free ===" RESET);
	show_alloc_mem();
	show_alloc_mem_ex();

	free(s1);
	free(s2);
	free(s3);
	free(s4);

	ft_printf(CYAN "\n=== Depois do Free ===" RESET);
	show_alloc_mem_ex();
}

static void	large_tests(void)
{
	char	*l1;
	char	*l2;
	char	*l3;
	char	*l4;

	ft_printf("%s\n*** Teste LARGE ***%s\n", YELLOW, RESET);

	l1 = malloc(1025);
	l2 = malloc(1088);
	l3 = malloc(2050);
	l4 = malloc(1280);

	ft_printf(CYAN "=== Antes do Free ===" RESET);
	show_alloc_mem();
	show_alloc_mem_ex();

	free(l1);
	free(l2);
	free(l3);
	free(l4);

	ft_printf(CYAN "\n=== Depois do Free ===" RESET);
	show_alloc_mem_ex();
}

static void	test_1(void)
{
	char	*str;

	ft_printf("%s\n*** Teste 1 ***%s\n", YELLOW, RESET);

	str = malloc(15 * sizeof(char));

	if (!str)
		ft_printf("%sError: Teste 1.1%s\n", RED, RESET);

	strcpy(str, "Hello Malloc!");
	ft_printf("str: %s\n\n", str);

	if (strcmp(str, "Hello Malloc!") != 0)
		ft_printf("%sError: Teste 1.2%s\n", RED, RESET);

	ft_printf(CYAN "=== Antes do Free ===" RESET);
	show_alloc_mem();
	show_alloc_mem_ex();

	free(str);

	ft_printf(CYAN "\n=== Depois do Free ===" RESET);
	show_alloc_mem_ex();
}

int	main(void)
{
	welcome();

	tiny_tests();
	small_tests();
	large_tests();

	test_1();

	goodbye();
	return (0);
}
