/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:48:46 by llopes-d          #+#    #+#             */
/*   Updated: 2023/06/22 14:55:47 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_flag;

void	signal_handler(int sig)
{
	g_flag = sig;
}

int	send_message(int pid, char a)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((a >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(800);
		bit--;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int	i;
	int	server_pid;

	if (argc != 3)
		return (1);
	i = 0;
	g_flag = 0;
	server_pid = ft_atoi_base(argv[1], 10);
	signal(SIGUSR1, signal_handler);
	while (argv[2][i])
		send_message(server_pid, argv[2][i++]);
	if (g_flag)
		write(1, "signal received by the server, exiting the program...", 54);
	return (0);
}
