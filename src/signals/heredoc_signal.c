/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:42:31 by eelissal          #+#    #+#             */
/*   Updated: 2025/07/04 14:46:35 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_heredoc(int signum)
{
	(void) signum;
	g_received_signal = SIGINT;
	rl_done = 1;
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa_int.sa_mask);
	sigaddset(&sa_int.sa_mask, SIGQUIT);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
