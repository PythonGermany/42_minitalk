/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 22:47:26 by rburgsta          #+#    #+#             */
/*   Updated: 2022/11/21 22:47:26 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"

unsigned char	nb;

void handle_signals(int sig)
{
	static int	bit;
	
	nb >>= 1;
	if (sig == SIGUSR2)
		nb += 128;
	bit++;
	if (bit == 8)
	{
		write(1, &nb, 1);
		nb = 0;
		bit = 0;
	}
}

int	main()
{
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_signals;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("%i\n", getpid());
	nb = 0;
	while (1);
	return (0);
}
