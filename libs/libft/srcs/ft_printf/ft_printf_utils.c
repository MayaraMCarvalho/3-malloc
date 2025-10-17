/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 02:59:18 by macarval          #+#    #+#             */
/*   Updated: 2022/07/01 19:04:59 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_putchar(char c, int *cont)
{
	*cont = *cont + 1;
	write(1, &c, 1);
}

void	ft_putstr(char *str, int *cont)
{
	if (!str)
		ft_putstr("(null)", cont);
	else
	{
		while (*str != '\0')
		{
			ft_putchar(*str, cont);
			str++;
		}
	}
}

void	ft_putnbr(int nb, int *cont)
{
	if (nb >= -2147483647 && nb <= 2147483647)
	{
		if (nb < 0)
		{
			ft_putchar('-', cont);
			nb = -nb;
		}
		if (nb >= 10)
		{
			ft_putnbr(nb / 10, cont);
			ft_putnbr(nb % 10, cont);
		}
		else
			ft_putchar(nb + '0', cont);
	}
	if (nb == -2147483648)
		ft_putstr("-2147483648", cont);
}

void	ft_puthexun(unsigned long int nb, char c, int *cont)
{
	unsigned long int	base;

	base = 10;
	if (c == 'x' || c == 'X' || c == 'p')
		base = 16;
	if (nb >= base)
	{
		ft_puthexun(nb / base, c, cont);
		ft_puthexun(nb % base, c, cont);
	}
	else if ((c == 'x' || c == 'X' || c == 'p')
		&& nb >= 10 && nb <= 15)
	{
		if (c == 'x' || c == 'p')
			ft_putchar(nb + 87, cont);
		if (c == 'X')
			ft_putchar(nb + 55, cont);
	}
	else
		ft_putchar(nb + '0', cont);
}
