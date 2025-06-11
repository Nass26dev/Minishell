/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:33:45 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/11 15:24:41 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

int minishell_loop(void)
{
	static t_data data;
	char *input;

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
	
	// printf("avant concatenation :\n");
	// t_token *tmp;
	// tmp = data.tokens;
	// while (tmp)
	// {
	// 	printf("value : %s, tag = %d, space = %d\n", tmp->value, tmp->tag, tmp->space);
	// 	tmp = tmp->next;
	// }
	
	// printf("apres concatenation :\n");
	// tmp = data.tokens;
	// while (tmp)
	// {
	// 	printf("value : %s, tag = %d, space = %d\n", tmp->value, tmp->tag, tmp->space);
	// 	tmp = tmp->next;
	// }

	// parser(&data, data.tokens, find_last_node(data.tokens));
	free_tokens(&data.tokens);
	// if (data.ast)
	// 	execute(data.ast, data.shell);
	return (0);
}
