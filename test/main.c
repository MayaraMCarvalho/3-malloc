/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:30:01 by macarval          #+#    #+#             */
/*   Updated: 2026/04/11 21:58:01 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "colors.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	welcome(void);
void	goodbye(void);

int	main(void)
{
	char	*t1, *t2, *t3, *t4;
	char	*s1, *s2, *s3, *s4;
	char	*l1, *l2, *l3, *l4;

	welcome();

	// Teste TINY
	t1 = malloc(12);
	t2 = malloc(5);
	t3 = malloc(1);
	t4 = malloc(128);

	// Teste SMALL
	s1 = malloc(129);
	s2 = malloc(523);
	s3 = malloc(679);
	s4 = malloc(1024);

	// Teste LARGE
	l1 = malloc(1025);
	l2 = malloc(1088);
	l3 = malloc(2050);
	l4 = malloc(1280);

	ft_printf("\n[Ponteiros]: %p %p %p %p\n", t1, t2, t3, t4);
	ft_printf("[Ponteiros]: %p %p %p %p\n", s1, s2, s3, s4);
	ft_printf("[Ponteiros]: %p %p %p %p\n\n", l1, l2, l3, l4);

	show_alloc_mem();

	t1[0] = 'H';

	ft_printf("Antes do free: %s\n", t1);
	free(t1);
	ft_printf("Depois do free: %s\n", t1);

	free(t2);
	free(t3);
	free(t4);

	free(s1);
	free(s2);
	free(s3);
	free(s4);

	free(l1);
	free(l2);
	free(l3);
	free(l4);

	show_alloc_mem();
	goodbye();
	return (0);
}
