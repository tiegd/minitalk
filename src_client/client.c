/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:21 by gaducurt          #+#    #+#             */
/*   Updated: 2025/02/25 18:37:30 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "ft_printf.h"

void    handle_signal(int signal)
{
    (void)signal;
    ft_printf("signal");
}

int main(int ac, char **av)
{
    // signal(SIGUSR1, handle_signal);
    // signal(SIGUSR2, handle_signal);
    if (ac != 3)
		return (0);
	
    (void) av;
}
