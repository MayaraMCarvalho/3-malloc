/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:23:34 by macarval          #+#    #+#             */
/*   Updated: 2025/10/21 11:48:08 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	ft_printf("\n%s--- NOSSO MALLOC FOI CHAMADO! ---%s\n\n", BGREEN, RESET);

	if (size) {}
		//fazer malloc
	return NULL;
}
