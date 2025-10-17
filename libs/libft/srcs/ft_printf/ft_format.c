/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:21:52 by macarval          #+#    #+#             */
/*   Updated: 2022/07/01 19:04:42 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_pdi(va_list res, char j, int *cont)
{
	long int	num;

	num = va_arg(res, int);
	if (num >= 0)
		ft_putchar(j, cont);
	ft_putnbr(num, cont);
}

int	ft_p_sender_ipceplus(va_list res, const char *str, int i, int *cont)
{
	char		j;
	int			k;
	int			rep;
	char		*s;

	rep = 0;
	j = str[i];
	while (str[i] != 'd' && str[i] != 'i' && str[i] != 's')
	{
		if (str[i] > 47 && str[i] < 58)
			rep = rep * 10 + str[i] - 48;
		i++;
	}
	if (str[i] == 'd' || str[i] == 'i')
		ft_pdi(res, j, cont);
	if (str[i] == 's')
	{
		s = va_arg(res, char *);
		k = ft_strlen(s);
		while (rep > 0 && k++ < rep)
			ft_putchar(j, cont);
		ft_putstr(s, cont);
	}
	return (i);
}

int	ft_format_plus(va_list res, const char *str, int i, int *cont)
{
	long int	num;

	if (str[i] == '#')
	{
		i++;
		if (str[i] == 'x' || str[i] == 'X')
		{
			num = va_arg(res, int);
			if (num != 0)
				*cont = *cont + ft_printf("%c%c", '0', str[i]);
			ft_puthex(num, str[i], cont);
		}
	}
	else if (str[i] == ' ' || str[i] == '+')
		i = ft_p_sender_ipceplus(res, str, i, cont);
	else
		ft_putchar(str[i], cont);
	return (i);
}
