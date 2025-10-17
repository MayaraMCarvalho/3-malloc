/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 20:59:24 by macarval          #+#    #+#             */
/*   Updated: 2024/10/24 17:14:58 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_format(va_list res, const char *str, int i, int *cont)
{
	if (str[i] == 37)
	{
		i++;
		if (str[i] == '%')
			ft_putchar('%', cont);
		else if (str[i] == 'i' || str[i] == 'd')
			ft_putnbr(va_arg(res, int), cont);
		else if (str[i] == 'c')
			ft_putchar(va_arg(res, int), cont);
		else if (str[i] == 's')
			ft_putstr(va_arg(res, char *), cont);
		else if (str[i] == 'p')
			ft_putptr(va_arg(res, long int), cont);
		else if (str[i] == 'u')
			ft_putun(va_arg(res, int), str[i], cont);
		else if (str[i] == 'x' || str[i] == 'X')
			ft_puthex(va_arg(res, int), str[i], cont);
		else
			i = ft_format_plus(res, str, i, cont);
	}
	else
		ft_putchar(str[i], cont);
	return (i);
}

void	ft_puthex(long int nb, char c, int *cont)
{
	if (nb < -2147483648 || nb > 9223372036854775807)
		ft_puthexun((unsigned long int) nb, c, cont);
	else if (nb >= -2147483648 && nb < 0)
	{
		if (c == 'p')
			ft_puthexun((unsigned long int) nb, c, cont);
		else
			ft_puthexun((unsigned int) nb, c, cont);
	}
	else
		ft_puthexun(nb, c, cont);
}

void	ft_putun(int nb, char c, int *cont)
{
	unsigned int	num;

	if (nb < 0)
	{
		num = (unsigned int) nb;
		ft_puthexun(num, c, cont);
	}
	else
		ft_puthexun(nb, c, cont);
}

void	ft_putptr(long int ptr, int *cont)
{
	if (!ptr)
		ft_putstr("(nil)", cont);
	else
	{
		ft_putstr("0x", cont);
		ft_puthex(ptr, 'p', cont);
	}
}
