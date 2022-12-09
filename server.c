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

void	handle_signals(int sig, siginfo_t *sginfo, void *imhere)
{
	static int				bit;
	static unsigned char	nb;

	(void)imhere;
	nb >>= 1;
	if (sig == SIGUSR2)
		nb += 128;
	bit++;
	if (bit == 8)
	{
		write(1, &nb, 1);
		if (!nb)
			kill(sginfo->si_pid, SIGUSR2);
		nb = 0;
		bit = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handle_signals;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("%i\n", getpid());
	while (1)
		pause();
	return (0);
}
