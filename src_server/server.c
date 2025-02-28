/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:33 by gaducurt          #+#    #+#             */
/*   Updated: 2025/02/28 17:25:23 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*str;

char	ft_btoi()
{
	
}

void    handle_signal(int signal, siginfo_t *info, void *context)
{
	static size_t	bin;
	int				nb;

    (void)info;
	(void)context;
    ft_printf("%s", str);
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
