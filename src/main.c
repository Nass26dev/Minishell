/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:55:02 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/07 01:10:47 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	// t_shell	shell;

	(void) argv;
	//check si un seul argc: il ne doit pas y avoir d'autres arg après ./minishell
	(void) argc;
	//init shell
	(void) envp;
	// if (init_shell(&shell, envp) == false)
		// return (1);
	setup_interactive_signals();
	while (1)
		minishell_loop();
	return (0);
	//free shell
}
