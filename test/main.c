/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:30:01 by macarval          #+#    #+#             */
/*   Updated: 2026/04/11 22:05:43 by macarval         ###   ########.fr       */
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

	t1[0] = 1; t2[0] = 1; t3[0] = 1; t4[0] = 1;

	// Teste SMALL
	s1 = malloc(129);
	s2 = malloc(523);
	s3 = malloc(679);
	s4 = malloc(1024);

	s1[0] = 2; s2[0] = 2; s3[0] = 2; s4[0] = 2;

	// Teste LARGE
	l1 = malloc(1025);
	l2 = malloc(1088);
	l3 = malloc(2050);
	l4 = malloc(1280);

	l1[0] = 3; l2[0] = 3; l3[0] = 3; l4[0] = 3;

	ft_printf(CYAN "=== Antes do Free ===" RESET);
	show_alloc_mem();

	free(t1); free(t2); free(t3); free(t4);
    free(s1); free(s2); free(s3); free(s4);
    free(l1); free(l2); free(l3); free(l4);

	ft_printf(CYAN "\n=== Depois do Free ===" RESET);
	show_alloc_mem();


	goodbye();
	return (0);
}
