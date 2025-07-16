/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:33:11 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/04 18:35:40 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_received_signal = 0;

void	display_welcome_message(void)
{
	printf("%s", BLUE);
	printf("╔══════════════════════════════════════╗\n");
	printf("║                                      ║\n");
	printf("║%s      👋 WELCOME TO MINISHELL 👋      %s║\n", PURPLE, BLUE);
	printf("║                                      ║\n");
	printf("╚══════════════════════════════════════╝\n");
	printf("%s", RESET);
}

bool	check_error(t_shell *shell, int argc, char **envp)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)
		|| !isatty(STDERR_FILENO))
	{
		ft_putstr_fd("minishell: This program ", STDERR_FILENO);
		ft_putstr_fd("must be run in a standard terminal\n", STDERR_FILENO);
		return (1);
	}
	if (argc != 1)
	{
		ft_putstr_fd("minishell: no arguments allowed\n", STDERR_FILENO);
		return (1);
	}
	if (init_shell(shell, envp) == false)
	{
		ft_putstr_fd("minishell: failed env initialization\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		status;

	(void)argv;
	if (check_error(&shell, argc, envp))
		return (1);
	setup_interactive_signals();
	display_welcome_message();
	while (1)
	{
		if (minishell_loop(&shell) == 1)
			break ;
	}
	status = shell.status;
	free_shell(&shell);
	rl_clear_history();
	return (status);
}
