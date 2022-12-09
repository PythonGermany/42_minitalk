/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburgsta <rburgsta@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 22:51:37 by rburgsta          #+#    #+#             */
/*   Updated: 2022/11/21 22:51:37 by rburgsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "libft/libft.h"

int g_send;

void	handle_sig(int sig)
{
	if (sig == SIGUSR2)
	{
		write(1, "Message recieved!\n", 18);
		exit(0);
	}
	else if (sig == SIGINT)
		g_send = 0;
}

void	send_char(unsigned char c, int server_pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c % 2 == 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		c >>= 1;
		usleep(100);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int	i;

	if (argc != 3)
	{
		ft_printf("%s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	if (!ft_atoi(argv[1]) || kill(ft_atoi(argv[1]), 0))
	{
		ft_printf("\"%s\" is not a valid pid\n", argv[1]);
		return (1);
	}
	signal(SIGUSR2, &handle_sig);
	signal(SIGINT, &handle_sig);
	i = 0;
	g_send = 1;
	while (g_send && argv[2][i])
		send_char((unsigned char)argv[2][i++], ft_atoi(argv[1]));
	if (g_send)
	{
		send_char(argv[2][i], ft_atoi(argv[1]));
		pause();
	}
	return (0);
}
