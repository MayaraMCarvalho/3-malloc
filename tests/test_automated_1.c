/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_automated_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:06:29 by macarval          #+#    #+#             */
/*   Updated: 2026/04/17 19:05:59 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

int	test_1(void)
{
	char	*str;

	str = malloc(15);
	if (!str)
		return (1);
	ft_strlcpy(str, "Hello Malloc!", 14);
	if (ft_strncmp(str, "Hello Malloc!", 14) != 0)
		return (1);
	free(str);
	return (0);
}

int	test_2(void)
{
	void	*ptr;

	ptr = malloc(0);
	free(ptr);
	return (0);
}

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
	ft_strlcpy(t1, "Tiny1", 6);
	ft_strlcpy(s1, "Small1", 7);
	ft_strlcpy(t2, "Tiny2", 6);
	if (ft_strncmp(t1, "Tiny1", 6) != 0
		|| ft_strncmp(s1, "Small1", 7) != 0
		|| ft_strncmp(t2, "Tiny2", 6) != 0)
		return (1);
	free(t1);
	free(s1);
	free(t2);
	return (0);
}

int	test_4(void)
{
	char	*str;

	str = malloc(10);
	if (!str)
		return (12);
	ft_strlcpy(str, "Test", 5);
	str = realloc(str, 50);
	if (!str || ft_strncmp(str, "Test", 5) != 0)
		return (1);
	free(str);
	return (0);
}

int	test_5(void)
{
	char	*ptr;

	ptr = realloc(NULL, 42);
	if (!ptr)
		return (1);
	ft_strlcpy(ptr, "Passed", 42);
	ptr = realloc(ptr, 0);
	if (ptr != NULL)
		return (1);
	return (0);
}
