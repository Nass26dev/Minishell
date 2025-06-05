/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:58:12 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/05 12:55:33 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_exec.h"

void minishell_loop(void)
{
	static t_data data;
	t_shell	*shell;
	t_ast	*ast;

	get_line_and_add_to_historical(&data);
	lexer(&data);
	error_checker(&data);
	parser(&data);
	if (ast)
		execute(ast, shell);
}
