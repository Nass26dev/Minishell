/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/25 18:38:29 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	received_signal = 0;

void	display_welcome_message(void)
{
	const char *blue = "\033[1;34m";     // Bleu clair
	const char *purple = "\033[1;35m";   // Violet
	const char *reset = "\033[0m";       // Réinitialise les couleurs

	printf("%s", blue);
	printf("╔══════════════════════════════════════╗\n");
	printf("║                                      ║\n");
	printf("║%s      👋 WELCOME TO MINISHELL 👋      %s║\n", purple, blue);
	printf("║                                      ║\n");
	printf("╚══════════════════════════════════════╝\n");
	printf("%s", reset);
}

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argv;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || !isatty(STDERR_FILENO))
	{
		ft_putstr_fd("minishell: This program must be run in a standard terminal\n", STDERR_FILENO);
		return (1);
	}
	if (argc != 1)
	{
		ft_putstr_fd("minishell: no arguments allowed\n", STDERR_FILENO);
		return (1);
	}
	if (init_shell(&shell, envp) == false)
	{
		ft_putstr_fd("minishell: failed env initialization\n", STDERR_FILENO);
		return (1);
	}
	setup_interactive_signals();
	display_welcome_message();
	while (1)
	{
		if (minishell_loop(&shell) == 1)
			break ;
	}
	free_shell(&shell);
	rl_clear_history();
	return (0);
}
