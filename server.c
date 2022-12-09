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
#include <stdlib.h>
#include <sys/errno.h>
#include "libft/libft.h"

char	*g_message;

static char	*ft_cpappend(char *dst, char *src)
{
	int		dst_size;
	int		src_size;
	char	*buf;

	src_size = ft_strlen(src);
	dst_size = 0;
	if (dst)
		dst_size = ft_strlen(dst);
	buf = ft_calloc(1, dst_size + src_size + 1);
	if (buf)
	{
		while (src_size-- > 0)
			buf[dst_size + src_size] = src[src_size];
		while (dst_size-- > 0)
			buf[dst_size] = dst[dst_size];
	}
	if (dst)
		free(dst);
	return (buf);
}

void	handle_exit(int sig)
{
	if (sig == SIGINT)
	{
		if (g_message)
			free(g_message);
		g_message = 0;
	}
	exit(0);
}

void	process_string(unsigned char c, siginfo_t *sginfo)
{
	static char				buffer[100];
	static int				i;

	buffer[i++] = c;
	if (i >= 99 || !c)
	{
		buffer[i] = 0;
		g_message = ft_cpappend(g_message, buffer);
		if (!g_message)
			exit(errno);
		i = 0;
	}
	if (!c)
	{
		write(1, g_message, ft_strlen(g_message));
		free(g_message);
		g_message = 0;
		kill(sginfo->si_pid, SIGUSR2);
	}
}

void	handle_signals(int sig, siginfo_t *sginfo, void *imhere)
{
	static int				bit;
	static unsigned char	c;

	(void)imhere;
	c >>= 1;
	if (sig == SIGUSR2)
		c += 128;
	if (++bit == 8)
	{
		process_string(c, sginfo);
		c = 0;
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
	signal(SIGINT, &handle_exit);
	ft_printf("PID: %i\n", getpid());
	while (1)
		pause();
	return (0);
}
