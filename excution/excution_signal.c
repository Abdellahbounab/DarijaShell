/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_signal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:36:37 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 11:26:27 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

void	signal_handler(int sig)
{
	(void)sig;
	g_status = 1;
	rl_replace_line("", 0);
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	ft_signals(int child)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (child)
	{
		if (child == 1)
			sigaction(SIGINT, &sa, NULL);
		else
			signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	return (1);
}
