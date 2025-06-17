/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:33:45 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/17 19:44:03 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

int minishell_loop(void)
{
	static t_data data;
	char *input;
	// t_token *tmp;

	if (get_input_and_add_to_historical(&input) == 1)
		return (1);
	lexer(&data, input);
	if (data.error == true)
	{
		data.error = false;
		return (0);
	}
	free(input);
	// printf("avant concatenation :\n");
	// tmp = data.tokens;
	// while (tmp)
	// {
	// 	printf("value : %s, tag = %d, space = %d\n", tmp->value, tmp->tag, tmp->space);
	// 	tmp = tmp->next;
	// }
	expander(&data);
	if (data.error == true)
	{
		data.error = false;
		return (0);
	}
	error_checker(&data);
	if (data.error == true)
	{
		data.error = false;
		return (0);
	}
	
	// printf("apres concatenation :\n");
	// tmp = data.tokens;
	// while (tmp)
	// {
	// 	printf("value : %s, tag = %d, space = %d\n", tmp->value, tmp->tag, tmp->space);
	// 	tmp = tmp->next;
	// }

	data.ast = parser(&data, data.tokens, find_last_node(data.tokens));
	print_ast(data.ast, 0);
	free_tokens(&data.tokens);
	// if (data.ast)
	// 	execute(data.ast, data.shell);
	return (0);
}
