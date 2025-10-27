/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:32:45 by marvin            #+#    #+#             */
/*   Updated: 2025/10/27 18:32:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    welcome(void)
{
    ft_printf("%s", BPURPLE);
    ft_printf("\n╔════════════════════════════════════════════════════╗\n");
    ft_printf("║                                                    ║\n");
    ft_printf("║         🚀  Bem-vindo ao Projeto Malloc! 🚀        ║\n");
    ft_printf("║                                                    ║\n");
    ft_printf("╚════════════════════════════════════════════════════╝\n");
    ft_printf("%s", RESET);
}

void    goodbye(void)
{
    ft_printf("%s", BCYAN);
    ft_printf("\n╔════════════════════════════════════════════════════╗\n");
    ft_printf("║                                                    ║\n");
    ft_printf("║       ✅ Execução finalizada com sucesso!          ║\n");
    ft_printf("║                                                    ║\n");
    ft_printf("╚════════════════════════════════════════════════════╝\n");
    ft_printf("%s", RESET);
}