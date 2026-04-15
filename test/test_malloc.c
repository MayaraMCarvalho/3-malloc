/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* test_malloc.c                                      :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/04/14 21:25:45 by macarval          #+#    #+#             */
/* Updated: 2026/04/14 22:00:00 by macarval         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "colors.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


/* ========================================================================== */
/* TESTES AUTOMATIZADOS (SILENCIOSOS)                    */
/* ========================================================================== */

int test_1(void) // ID 1
{
	char    *str;
	str = malloc(15);
	if (!str) return (1);
	strcpy(str, "Hello Malloc!");
	if (strcmp(str, "Hello Malloc!") != 0) return (1);
	free(str);
	return (0);
}

int test_2(void) // ID 2
{
	void    *ptr = malloc(0);
	free(ptr);
	return (0);
}

int test_3(void) // ID 3
{
	char    *t1 = malloc(16);
	char    *s1 = malloc(512);
	char    *t2 = malloc(32);
	if (!t1 || !s1 || !t2) return (1);
	strcpy(t1, "Tiny1"); strcpy(s1, "Small1"); strcpy(t2, "Tiny2");
	if (strcmp(t1, "Tiny1") != 0 || strcmp(s1, "Small1") != 0 || strcmp(t2, "Tiny2") != 0)
		return (1);
	free(t1); free(s1); free(t2);
	return (0);
}

int test_4(void) // ID 4
{
	char    *str = malloc(10);
	if (!str) return (1);
	strcpy(str, "Teste");
	str = realloc(str, 50);
	if (!str || strcmp(str, "Teste") != 0) return (1);
	strcat(str, " Expandido");
	if (strcmp(str, "Teste Expandido") != 0) return (1);
	free(str);
	return (0);
}

int test_5(void) // ID 5
{
	char    *ptr = realloc(NULL, 42);
	if (!ptr) return (1);
	strcpy(ptr, "Sobrevivi");
	ptr = realloc(ptr, 0);
	if (ptr != NULL) return (1);
	return (0);
}

int test_6(void) // ID 6
{
	void    *arr[100];
	int     i = 0, j;
	while (i < 10)
	{
		j = 0;
		while (j < 100) { arr[j] = malloc(128); if (!arr[j]) return (1); j++; }
		j = 0;
		while (j < 100) { free(arr[j]); j++; }
		i++;
	}
	return (0);
}

/* ========================================================================== */
/* TESTES VISUAIS E CASOS COMPLEXOS                       */
/* ========================================================================== */

int test_7_tiny(void) // ID 7
{
	char    *t1 = malloc(12); char  *t2 = malloc(5); char   *t3 = malloc(128);
	ft_printf("\n%s*** Test TINY ***%s\n", YELLOW, RESET);
	t1[0] = 'A'; t2[0] = 'B'; t3[0] = 'C';
	show_alloc_mem_ex();
	free(t1); free(t2); free(t3);
	ft_printf(CYAN "\n=== After Free ===\n" RESET);
	show_alloc_mem_ex();
	return (0);
}

int test_8_small(void) // ID 8
{
	char    *s1 = malloc(129); char *s2 = malloc(523); char *s3 = malloc(1024);
	ft_printf("\n%s*** Test SMALL ***%s\n", YELLOW, RESET);
	s1[0] = 'E'; s2[0] = 'F'; s3[0] = 'G';
	show_alloc_mem_ex();
	free(s1); free(s2); free(s3);
	ft_printf(CYAN "\n=== After Free ===\n" RESET);
	show_alloc_mem_ex();
	return (0);
}

int test_9_large(void) // ID 9
{
	char    *l1 = malloc(1025); char *l2 = malloc(1088); char *l3 = malloc(2050);
	ft_printf("\n%s*** Test LARGE ***%s\n", YELLOW, RESET);
	show_alloc_mem_ex();
	free(l1); free(l2); free(l3);
	ft_printf(CYAN "\n=== After Free ===\n" RESET);
	show_alloc_mem_ex();
	return (0);
}

int test_10_edge_cases(void) // ID 10
{
	void	*ptr1;
	void	*ptr2;

	ft_printf("\n%s*** TESTE DE CASOS EXTREMOS ***%s\n", YELLOW, RESET);
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
	ft_printf("[5] free(ponteiro_invalido)...\n");
	free((void *)0xDEADBEEF);
	ft_printf("%s-> Casos extremos sobreviveram sem Segfault!%s\n", GREEN, RESET);
	return (0);
}

int test_11_fragmentation(void) // ID 11
{
	void *a = malloc(128); void *b = malloc(128); void *c = malloc(128);
	ft_printf("\n%s*** TESTE DE FRAGMENTACAO E COALESCING ***%s\n", YELLOW, RESET);
	ft_printf("-> Alocados 3 blocos. Liberando as pontas (A e C)...\n");
	free(a); free(c);
	ft_printf("-> Liberando o meio (B). Deve formar um Megabloco.\n");
	free(b);
	show_alloc_mem_ex();
	return (0);
}
