/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:48:28 by eelissal          #+#    #+#             */
/*   Updated: 2025/06/19 14:24:53 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_received_signal = 0;

/*For the SIGINT signal prints a newline and redisplays the prompt*/
void	handle_sigint(int signum)
{
	g_received_signal = signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
	
/*Handles signals in interactive mode:
- SIGINT (Ctrl-C): handles the signal (with handle_sigint)
- SIGQUIT (Ctrl-\): ignores the signal (with SIG_IGN)
For each signal, sigemtyset initializes the signal set handled to empty.
The signal mask defines which signals are blocked while the signal handler
is executed.
Then, sigaddset blocks the other signal to prevent race conditions and handler
reentrance issues.
Then, sigaction registers the signal handler for either SIGINT or SIGQUIT.
The null parameter indicates the previous handler signal is not stored.
Flags are set to the default behaviour.*/
void	setup_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sigaddset(&sa_int.sa_mask, SIGQUIT);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sigaddset(&sa_quit.sa_mask, SIGINT);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/*Handles both SIGINT and SIGQUIT signals in a child process, which is not
interactive. SIG_DFL is the default signal handling.*/
void	setup_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
