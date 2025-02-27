/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:21 by gaducurt          #+#    #+#             */
/*   Updated: 2025/02/27 16:31:53 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_msg(int pid, char *msg)
{
	int	i;
	int	j;

	i = 0;
	while (msg[i])
	{
		j = 0;
		while (j++ <= 8)
		{
			if ((msg[i] >> (7 - j) & 1) == 0)
				kill(pid, SIGUSR1);
			else if ((msg[i] >> (7 - j) & 1) == 1)
				kill(pid, SIGUSR2);
		}
		i++;
	}
	j = 0;
	while (j++ <= 8)
		kill(pid, SIGUSR1);
}

// void	handle_signal(int signal)
// {
// 	(void)signal;
// 	ft_printf("signal");
// }

int	main(int ac, char **av)
{
	// signal(SIGUSR1, handle_signal);
	// signal(SIGUSR2, handle_signal);
	// if (ac != 3)
	// 	return (0);
	// (void) av;
	int		pid;
	char	*msg;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		msg = av[2];
		ft_printf("%d\n", pid);
		ft_printf("%s", msg);
		send_msg(pid, msg);
	}
	else
		return (0);
}
