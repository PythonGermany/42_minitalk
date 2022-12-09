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
#include <signal.h>
#include "libft/libft.h"

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
		usleep(1000);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int	i;

	if (argc != 3)
		ft_printf("%s <server_pid> <message>\n", argv[0]);
	i = 0;
	while (argv[2][i])
		send_char((unsigned char)argv[2][i++] ,ft_atoi(argv[1]));
	send_char(argv[2][i] ,ft_atoi(argv[1]));
	return (0);
}
