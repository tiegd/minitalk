/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:33 by gaducurt          #+#    #+#             */
/*   Updated: 2025/03/17 13:26:55 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <sys/time.h>

char	*g_str;

static void	ft_fill_str(int nb)
{
	int	i;

	i = 0;
	if (g_str[i] == '\0')
	{
		g_str[i] = nb;
		return ;
	}
	while (g_str[i])
		i++;
	g_str[i] = nb;
}

static int	ft_btoi(int nb, int signal)
{
	if (signal == SIGUSR1)
		nb = (nb << 1) | 0;
	if (signal == SIGUSR2)
		nb = (nb << 1) | 1;
	return (nb);
}

void    handle_signal(int signal, siginfo_t *info, void *context)
{
	static int		nb = 0;
	static int		count_size = 0;
	static int		count_bit = 0;
	static int		size = 0;

	(void)context;
	if (count_size++ <= 31)
		size = ft_btoi(size, signal);
	if (count_size == 32)
	{
		g_str = ft_calloc((size + 1), sizeof(char));
		count_size++;
	}
	if (count_size > 32 && count_bit++ <= 7)
	{
		if (count_size == 33)
			count_size++;
		else
			nb = ft_btoi(nb, signal);
	}
	if (count_size > 32 && count_bit == 8 && nb != 0)
	{
		ft_fill_str(nb);
		count_bit = 0;
		nb = 0;
	}
	else if (count_size > 32 && nb == 0 && count_bit == 8)
	{
		ft_printf("%s\n", g_str);
		free(g_str);
		count_size = 0;
		size = 0;
		count_bit = 0;
		nb = 0;
	}
	usleep(100);
	kill(info->si_pid, SIGUSR1);
}

int main()
{
	struct sigaction	action;
	
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	ft_printf("%d\n", getpid());
	while (1)
		continue ;
}
