/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:33 by gaducurt          #+#    #+#             */
/*   Updated: 2025/03/17 16:51:08 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <sys/time.h>

static void	ft_fill_str(int nb, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
	{
		str[i] = nb;
		return ;
	}
	while (str[i])
		i++;
	str[i] = nb;
}

static int	ft_btoi(int nb, int signal)
{
	if (signal == SIGUSR1)
		nb = (nb << 1) | 0;
	if (signal == SIGUSR2)
		nb = (nb << 1) | 1;
	return (nb);
}

static t_signal_data	ft_init_data(t_signal_data data, int signal)
{
	if (data.count_size == 33)
		data.count_size++;
	else
		data.nb = ft_btoi(data.nb, signal);
	return (data);
}

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static t_signal_data	data = {0, 0, 0, 0};
	static char				*str = NULL;

	(void)context;
	if (data.count_size++ <= 31)
		data.size = ft_btoi(data.size, signal);
	if (data.count_size == 32)
	{
		str = ft_calloc((data.size + 1), sizeof(char));
		data.count_size++;
	}
	if (data.count_size > 32 && data.count_bit++ <= 7)
		data = ft_init_data(data, signal);
	if (data.count_size > 32 && data.count_bit == 8 && data.nb != 0)
	{
		ft_fill_str(data.nb, str);
		data = (t_signal_data){0, data.count_size, 0, data.size};
	}
	else if (data.count_size > 32 && data.nb == 0 && data.count_bit == 8)
	{
		ft_printf("%s\n", str);
		free(str);
		data = (t_signal_data){0, 0, 0, 0};
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	ft_printf("%d\n", getpid());
	while (1)
		pause();
}
