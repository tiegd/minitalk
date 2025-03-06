/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:21 by gaducurt          #+#    #+#             */
/*   Updated: 2025/03/05 17:58:56 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	recived = 1;

void	handle_recived(int signal, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	// (void)signal;
	if (signal == SIGUSR1)
		recived = 0;
}

static void	ft_send_size(int pid, int size)
{
	int	i;

	i = 31;
	while (i >= 0)
	{
		if ((size >> i & 1) == 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(EXIT_FAILURE);
		}
		else if ((size >> i & 1) == 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		}
		while (recived)
		{
			ft_printf("boucle pause size\n");
			pause();
		}
		recived = 1;
		ft_printf("sortie de boucle pause size\n");
	// usleep(15000);
		i--;
	}
}

static void	ft_send_msg(int pid, char *msg)
{
	int	i;
	int	j;

	i = 0;
	while (msg[i])
	{
		j = 7;
		while (j-- >= 0)
		{
			if ((msg[i] >> j & 1) == 0)
			{
				if (kill(pid, SIGUSR1) == -1)
					exit(EXIT_FAILURE);
			}
			else if ((msg[i] >> j & 1) == 1)
			{
				if (kill(pid, SIGUSR2) == -1)
					exit(EXIT_FAILURE);
			}
			while (recived)
			{
				ft_printf("boucle pause msg\n");
				pause();
			}
			recived = 1;
			ft_printf("sortie de boucle pause msg\n");
			usleep(15000);
		}
		i++;
	}
	j = 0;
	while (j++ < 8)
	{
		kill(pid, SIGUSR1);
		usleep(15000);
	}
}

int	main(int ac, char **av)
{
	int					pid;
	char				*msg;
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handle_recived;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		msg = av[2];
		ft_send_size(pid, ft_strlen(av[2]));
		ft_send_msg(pid, msg);
	}
	else
		return (0);
}
