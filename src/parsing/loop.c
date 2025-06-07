/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:33:45 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/07 00:53:04 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

void minishell_loop(void)
{
	static t_data data;
	char *input;
	t_ast	*ast;
	t_shell	*shell;

	get_input_and_add_to_historical(&data, &input);
	lexer(&data, input);
	if (data.error == true)
	{
		data.error = false;
		return ;
	}
	free(input);
	expander(&data);
	
	t_token *tmp;
	tmp = data.tokens;
	while (tmp)
	{
		printf("value : %s, tag = %d, space = %d\n", tmp->value, tmp->tag, tmp->space);
		tmp = tmp->next;
	}
	// concatenate
	// error_checker(&data);
	// parser(&data);
	free_tokens(&data.tokens);
	ast = NULL;
	shell = NULL;
	if (ast)
		execute(ast, shell);
}
