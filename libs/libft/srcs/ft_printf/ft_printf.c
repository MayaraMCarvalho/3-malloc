/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 02:27:42 by macarval          #+#    #+#             */
/*   Updated: 2022/07/01 19:04:50 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_printf(const char *str, ...)
{
	va_list	res;
	int		i;
	int		num;
	int		*cont;

	i = 0;
	num = 0;
	cont = &num;
	va_start(res, str);
	while (str[i])
	{
		i = ft_format(res, str, i, cont);
		i++;
	}
	va_end(res);
	return (*cont);
}
