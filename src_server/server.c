/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:33 by gaducurt          #+#    #+#             */
/*   Updated: 2025/02/27 16:29:01 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	ft_convert()
{
	
}

void    handle_signal(int signal, siginfo_t *info, void *context)
{
    (void)info;
	(void)context;
    ft_printf("%d", signal);
}

int main()
{
	struct sigaction    action;

	action.sa_flags = SA_SIGINFO | SA_NODEFER;
	action.sa_sigaction = handle_signal;
	// sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	ft_printf("%d", getpid());
	while (1)
	{
		pause();
	}
}
