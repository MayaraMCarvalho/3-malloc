/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 21:25:45 by macarval          #+#    #+#             */
/*   Updated: 2026/04/14 21:39:46 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* Teste 1: Basic malloc() and data integrity */
int	test_1(void)
{
	char	*str;

	str = malloc(15);
	if (!str)
		return (1);
	strcpy(str, "Hello Malloc!");
	if (strcmp(str, "Hello Malloc!") != 0)
		return (1);
	free(str);
	return (0);
}

/* Teste 2: Edge case: malloc(0) */
int	test_2(void)
{
	void	*ptr;

	ptr = malloc(0);
	free(ptr);
	return (0);
}

/* Teste 3: Multiple allocations (Tiny/Small zones) */
int	test_3(void)
{
	char	*t1;
	char	*s1;
	char	*t2;

	t1 = malloc(16);
	s1 = malloc(512);
	t2 = malloc(32);
	if (!t1 || !s1 || !t2)
		return (1);
	strcpy(t1, "Tiny1");
	strcpy(s1, "Small1");
	strcpy(t2, "Tiny2");
	if (strcmp(t1, "Tiny1") != 0
		|| strcmp(s1, "Small1") != 0
		|| strcmp(t2, "Tiny2") != 0)
		return (1);
	free(t1);
	free(s1);
	free(t2);
	return (0);
}

/* Teste 4: Basic realloc() with data retention */
int	test_4(void)
{
	char	*str;

	str = malloc(10);
	if (!str)
		return (1);
	strcpy(str, "Teste");
	str = realloc(str, 50);
	if (!str)
		return (1);
	if (strcmp(str, "Teste") != 0)
		return (1);
	strcat(str, " Expandido");
	if (strcmp(str, "Teste Expandido") != 0)
		return (1);
	free(str);
	return (0);
}

/* Teste 5: Edge case: realloc(NULL) and realloc(0) */
int	test_5(void)
{
	char	*ptr;

	ptr = realloc(NULL, 42);
	if (!ptr)
		return (1);
	strcpy(ptr, "Sobrevivi");
	ptr = realloc(ptr, 0);
	if (ptr != NULL)
		return (1);
	return (0);
}

/* Teste 6: Stress test: 1000 loop allocations/frees */
int	test_6(void)
{
	void	*arr[100];
	int		i;
	int		j;

	i = 0;
	while (i < 10)
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
		i++;
	}
	return (0);
}

/* A porta de entrada: Lê o argumento passado pelo Bash */
int	main(int argc, char **argv)
{
	int	test_id;

	if (argc != 2)
		return (1);

	test_id = atoi(argv[1]);

	if (test_id == 1)
		return (test_1());
	if (test_id == 2)
		return (test_2());
	if (test_id == 3)
		return (test_3());
	if (test_id == 4)
		return (test_4());
	if (test_id == 5)
		return (test_5());
	if (test_id == 6)
		return (test_6());

	return (1);
}
