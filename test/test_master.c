/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 21:17:48 by macarval          #+#    #+#             */
/*   Updated: 2026/04/14 21:24:04 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "colors.h"

static void	test_edge_cases(void)
{
	void	*ptr1;
	void	*ptr2;

	ft_printf("\n%s*** EXTREME CASE TEST ***%s\n", YELLOW, RESET);
	ft_printf("[1] Testing malloc(0)...\n");
	ptr1 = malloc(0);
}
