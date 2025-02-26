/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:33 by gaducurt          #+#    #+#             */
/*   Updated: 2025/02/26 16:32:54 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    handle_signal(int signal, siginfo_t *info, void *context)
{
    (void)info;
	(void)context;
    ft_printf("%d", signal);
}

int main(int ac, char **av)
{
	// int					pid;
	struct sigaction    action;

	action.sa_flags = SA_SIGINFO | SA_NODEFER;
	action.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	// pid = getpid();
	// ft_printf("%d", pid);
	ft_printf("%d", getpid());
	while (1)
	{
		pause();
		// client(pid, av[1]);
	}
	(void) ac;
	(void) av;
}
