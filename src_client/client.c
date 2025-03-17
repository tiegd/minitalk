/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:21 by gaducurt          #+#    #+#             */
/*   Updated: 2025/03/17 16:40:17 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_recived(int signal, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (signal == SIGUSR1)
		return ;
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
		usleep(10000);
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
			usleep(10000);
		}
		i++;
	}
}

static void	ft_send_zero(int pid)
{
	int	j;

	j = 0;
	while (j++ < 7)
	{
		kill(pid, SIGUSR1);
		usleep(10000);
	}
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handle_recived;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (pid <= 0)
		{
			ft_putendl_fd("PID can´t be a negative or null number", 2);
			return (1);
		}
		ft_send_size(pid, ft_strlen(av[2]));
		ft_send_msg(pid, av[2]);
		ft_send_zero(pid);
	}
	if (ac != 3)
	{
		ft_putendl_fd("The client process need to take 2 parameters", 2);
		return (1);
	}
	return (0);
}
