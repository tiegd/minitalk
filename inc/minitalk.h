/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaducurt <gaducurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:38:25 by gaducurt          #+#    #+#             */
/*   Updated: 2025/03/17 14:22:52 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../Libft/libft.h"
# include "../Libft/ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>

typedef struct s_signal_data
{
	int	nb;
	int	count_size;
	int	count_bit;
	int	size;
}	t_signal_data;

#endif
