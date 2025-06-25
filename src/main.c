/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/25 16:54:43 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	received_signal = 0;

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argv;
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
	while (1)
	{
		if (minishell_loop(&shell) == 1)
			break ;
	}
	free_shell(&shell);
	rl_clear_history();
	return (0);
}
