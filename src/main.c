/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/24 15:33:56 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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
