/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_signal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:36:37 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/14 15:25:14 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"


void	signal_handler(int sig)
{
	(void) sig;
	status = 1;
	write (STDIN_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	ft_signals(int child)
{
	struct sigaction sa;

    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;  // Do not restart functions if interrupted
    sigemptyset(&sa.sa_mask);
    if (child) {
        if (child == 1)
            sigaction(SIGINT, &sa, NULL); //first time
		else
			signal(SIGINT, SIG_IGN); //parent process when forked
		signal(SIGQUIT, SIG_IGN); //both
	}
	else
	{
		signal(SIGINT, SIG_DFL); // child process when forked
		signal(SIGQUIT, SIG_DFL);
	}
	return 1;
}
