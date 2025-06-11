/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:33:45 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/11 09:38:29 by codespace        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

int minishell_loop(void)
{
	static t_data data;
	char *input;
	t_ast	*ast;
	t_shell	*shell;

	if (get_input_and_add_to_historical(&input) == 1)
		return (1);
	lexer(&data, input);
	if (data.error == true)
	{
		data.error = false;
		return (0);
	}
	free(input);
	expander(&data);
	
	// printf("avant concatenation :\n");
	// t_token *tmp;
	// tmp = data.tokens;
	// while (tmp)
	// {
	// 	printf("value : %s, tag = %d, space = %d\n", tmp->value, tmp->tag, tmp->space);
	// 	tmp = tmp->next;
	// }
	
	concatenation(&data);
	
	// printf("apres concatenation :\n");
	// tmp = data.tokens;
	// while (tmp)
	// {
	// 	printf("value : %s, tag = %d, space = %d\n", tmp->value, tmp->tag, tmp->space);
	// 	tmp = tmp->next;
	// }
	error_checker(&data);
	// parser(&data);
	free_tokens(&data.tokens);
	ast = NULL;
	shell = NULL;
	if (ast)
		execute(ast, shell);
	return (0);
}
