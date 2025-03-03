/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:33 by gaducurt          #+#    #+#             */
/*   Updated: 2025/03/03 18:18:29 by gaducurt         ###   ########.fr       */
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
	nb = nb << 1;
	if (signal == SIGUSR1)
		nb |= 0;
	if (signal == SIGUSR2)
		nb |= 1;
	ft_printf("nb dans ft_btoi = %d\n\n", nb);
	return (nb);
}

void    handle_signal(int signal)
{
	static int		nb = 0;
	static int		count_size = 0;
	static int		count_bit = 0;
	static int		size = 0;

    // (void)info;
	// (void)context;
	ft_printf("signal serv = %d\n", signal);
	if (count_size <= 32)
	{
		size = ft_btoi(size, signal);
		ft_printf("size = %d\n", size);
		ft_printf("count_size = %d\n", count_size);
		count_size++;
	}
	else if (count_size > 32)
		str = ft_calloc((size + 1), sizeof(char));
	// str = ft_calloc(7, sizeof(char));
	if (!str)
		return ;
	if (count_bit++ != 8)
	{
		nb = ft_btoi(nb, signal);
		ft_printf("nb = %d\n", nb);
	}
	ft_printf("count_bit = %d\n", count_bit);
	if (count_bit++ == 8 && nb != 0)
		ft_fill_str(nb);
	else if (count_bit == 8 && nb == 0)
	{
	    ft_printf("%s\n", str);
		free(str);
		count_size = 0;
		size = 0;
	}
	ft_printf("str = %s\n", str);
	count_bit = 0;
	nb = 0;
}

// void    handle_signal(int signal, siginfo_t *info, void *context)
// {
// 	static int		nb = 0;
// 	static int		count_size = 0;
// 	static int		count_bit = 0;
// 	static int		size = 0;

//     (void)info;
// 	(void)context;
// 	ft_printf("signal = %d\n", signal);
// 	if (count_size++ < 32)
// 		size = ft_btoi(size, signal, 31, count_size);
// 	if (count_size++ == 32)
// 		str = ft_calloc((size + 1), sizeof(char));
// 	if (!str)
// 		return ;
// 	if (count_bit++ == 8 && nb != 0)
// 		ft_fill_str(nb);
// 	else if (count_bit == 8 && nb == 0)
// 	{
// 	    ft_printf("%s\n", str);
// 		free(str);
// 		count_size = 0;
// 		size = 0;
// 	}
// 	count_bit = 0;
// 	nb = 0;
// }

// void    handle_signal2(int signal)
// {
// 	ft_printf("signal = %d\n", signal);
// }

int main()
{
	// struct sigaction    action;

	// sigemptyset(&action.sa_mask);
	// action.sa_flags = SA_SIGINFO | SA_NODEFER;
	// action.sa_sigaction = handle_signal;
	// sigaction(SIGUSR1, &action, NULL);
	// sigaction(SIGUSR2, &action, NULL);
	signal(SIGUSR1, &handle_signal);
	signal(SIGUSR2, &handle_signal);
	ft_printf("%d\n", getpid());
	while (1)
	{
		pause();
		// continue;
	}
}
