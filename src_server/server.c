/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:33 by gaducurt          #+#    #+#             */
/*   Updated: 2025/03/05 17:54:40 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*str;

static void	ft_fill_str(int nb)
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
	// ft_printf("nb dans ft_btoi = %d\n\n", nb);
	// ft_printf("\n");
	return (nb);
}

void    handle_signal(int signal, siginfo_t *info, void *context)
{
	static int		nb = 0;
	static int		count_size = 0;
	static int		count_bit = 0;
	static int		size = 0;

    (void)info;
	(void)context;
	// ft_printf("signal serv = %d\n", signal);
	if (count_size <= 31)
	{
		size = ft_btoi(size, signal);
		ft_printf("size = %d\n", size);
		ft_printf("count_size = %d\n", count_size);
		count_size++;
	}
	if (count_size == 32)
	{
		str = ft_calloc((size + 1), sizeof(char));
		// ft_printf("\n\ncalloc\n\n");
		if (!str)
			return ;
		count_size++;
	}
	if (count_size > 32 && count_bit++ <= 7)
	{
		nb = ft_btoi(nb, signal);
		// ft_printf("nb = %d\n", nb);
	}
	ft_printf("count_bit = %d\n", count_bit);
	if (count_size > 32 && count_bit == 8 && nb != 0)
	{
		ft_fill_str(nb);
		// ft_printf("\n\nrentre dans la boucle \n\n");
		// ft_printf("str = %s\n\n", str);
		count_bit = 0;
		nb = 0;
	}
	else if (count_size > 32 && nb == 0 && count_bit == 8)
	{
		ft_printf("%s\n", str);
		free(str);
		count_size = 0;
		size = 0;
		count_bit = 0;
		nb = 0;
	}
	// ft_printf("1 : info->si_pid = %d\n", info->si_pid);
	usleep(100);
	kill(info->si_pid, SIGUSR1);
	// ft_printf("str = %s\n\n", str);
}

int main()
{
	struct sigaction    action;

	sigemptyset(&action.sa_mask);
	// action.sa_flags = SA_SIGINFO | SA_NODEFER;
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	ft_printf("%d\n", getpid());
	while (1)
	{
		pause();
		// continue;
	}
}
