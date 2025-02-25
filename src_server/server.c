/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:33 by gaducurt          #+#    #+#             */
/*   Updated: 2025/02/25 18:37:21 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    handle_signal(int signal)
{
    (void)signal;
    ft_printf("%d", signal);
}

int main(int ac, char **av)
{
    struct sigaction    action;

    // action.sa_flags = SA_SIGINFO | SA.NODEFER;
    // action.sa_sigaction = handle_signal;
    // sigaction(SIGUSR1, &action, NULL);
    // sigaction(SIGUSR2, &action, NULL);
    while (1)
		pause();
    (void) ac;
    (void) av;
}
