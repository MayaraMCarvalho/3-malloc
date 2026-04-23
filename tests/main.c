/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:30:01 by macarval          #+#    #+#             */
/*   Updated: 2026/04/23 01:23:58 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include "colors.h"

void	welcome(void);
void	goodbye(void);
void	pause_evaluator(const char	*test_name);
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
int		test_16_alignment(void);
int		test_17_invalid_frees(void);
int		test_18_thread_safety(void);
int		test_19_realloc_large(void);

static void	complex_tests(void)
{
	welcome();
	test_7_tiny();
	pause_evaluator("Zones SMALL");
	test_8_small();
	pause_evaluator("Zones LARGE");
	test_9_large();
	pause_evaluator("Edge Cases");
	test_10_edge_cases();
	pause_evaluator("Fragmentation & Coalescing");
	test_11_fragmentation();
	pause_evaluator("Shrink Coalesce");
	test_14_shrink_coalesce();
	goodbye();
}

static int	run_part_1(int id)
{
	if (id == 1)
		return (test_1());
	if (id == 2)
		return (test_2());
	if (id == 3)
		return (test_3());
	if (id == 4)
		return (test_4());
	if (id == 5)
		return (test_5());
	if (id == 6)
		return (test_6());
	if (id == 7)
		return (test_7_tiny());
	if (id == 8)
		return (test_8_small());
	return (-1);
}

static int	run_part_2(int id)
{
	if (id == 9)
		return (test_9_large());
	if (id == 10)
		return (test_10_edge_cases());
	if (id == 11)
		return (test_11_fragmentation());
	if (id == 12)
		return (test_12_overlap());
	if (id == 13)
		return (test_13_massive());
	if (id == 14)
		return (test_14_shrink_coalesce());
	if (id == 15)
		return (test_15_expand_inplace());
	if (id == 16)
		return (test_16_alignment());
	if (id == 17)
		return (test_17_invalid_frees());
	if (id == 18)
		return (test_18_thread_safety());
	if (id == 19)
		return (test_19_realloc_large());
	return (-1);
}

int	main(int argc, char **argv)
{
	int	id;
	int	res;

	if (argc > 1)
	{
		id = ft_atoi(argv[1]);
		res = run_part_1(id);
		if (res != -1)
			return (res);
		return (run_part_2(id));
	}
	complex_tests();
	return (0);
}
