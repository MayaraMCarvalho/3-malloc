/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:30:01 by macarval          #+#    #+#             */
/*   Updated: 2026/04/17 18:47:32 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "colors.h"

void	welcome(void);
void	goodbye(void);
int		test_1(void);
int		test_2(void);
int		test_3(void);
int		test_4(void);
int		test_5(void);
int		test_6(void);
int		test_7_tiny(void);
int		test_8_small(void);
int		test_9_large(void);
int		test_10_edge_cases(void);
int		test_11_fragmentation(void);
int		test_12_overlap(void);
int		test_13_massive(void);
int		test_14_shrink_coalesce(void);
int		test_15_expand_inplace(void);

static void	complex_tests(void)
{
	welcome();
	test_7_tiny();
	test_8_small();
	test_9_large();
	test_10_edge_cases();
	test_11_fragmentation();
	test_12_overlap();
	test_13_massive();
	test_14_shrink_coalesce();
	test_15_expand_inplace();
	goodbye();
}

static int	run_test(int test_id)
{
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
	if (test_id == 7)
		return (test_7_tiny());
	if (test_id == 8)
		return (test_8_small());
	if (test_id == 9)
		return (test_9_large());
	if (test_id == 10)
		return (test_10_edge_cases());
	if (test_id == 11)
		return (test_11_fragmentation());
	if (test_id == 12)
		return (test_12_overlap());
	if (test_id == 13)
		return (test_13_massive());
	if (test_id == 14)
		return (test_14_shrink_coalesce());
	if (test_id == 15)
		return (test_15_expand_inplace());
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc > 1)
		return (run_test(ft_atoi(argv[1])));
	complex_tests();
	return (0);
}
