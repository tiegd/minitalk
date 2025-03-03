/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:33 by gaducurt          #+#    #+#             */
/*   Updated: 2025/03/03 12:58:27 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*str;

static int	ft_recursive_power(int nb, int power)
{
	int	i;

	i = 0;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, power - 1));
}

static int	ft_btoi(int nb, int signal, int nb_bit, int count)
{
	if (signal == SIGUSR1)
		nb = nb + 0;
	else if (signal == SIGUSR2)
		nb = nb + (1 * ft_recuscive_power(2, nb_bit - count));
	return (nb);
}

static void	ft_fill_str(int nb)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	str[i] = nb;
}

void    handle_signal(int signal, siginfo_t *info, void *context)
{
	static size_t	nb;
	static int		count_size;
	static int		count_bit;
	int				size;

    (void)info;
	(void)context;
	count_size = 0;
	if (count_size++ < 32)
		size = ft_btoi(size, signal, 31, count_size);
	if (count_size++ == 32)
		str = ft_calloc((size + 1), sizeof(char));
	if (!str)
		return ;
	if (count_bit++ == 8 && nb != 0)
		ft_fill_str(nb);
	else if (count_bit == 8 && nb == 0)
	{
	    ft_printf("%s\n", str);
		free(str);
	}
	count_bit = 0;
	nb = 0;
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
