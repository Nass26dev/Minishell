/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:33:45 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/19 18:01:44 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"

bool	is_error(bool *error)
{
	if (*error)
	{
		*error = false;
		return (1);
	}
	else
		return (0);
}

int	minishell_loop(t_shell *shell)
{
	static t_data	data;
	char			*input;
	// t_token *tmp;
	
	data.shell = shell;
	if (get_input_and_add_to_historical(&input) == 1)
		return (1);
	lexer(&data, input);
	if (is_error(&data.error))
		return (0);
	free(input);
	expander(&data);
	if (is_error(&data.error))
		return (0);
	error_checker(&data);
	if (is_error(&data.error))
		return (0);
	// tmp = data.tokens;
	// while (tmp)
	// {
	// 	printf("tag = %d, value = %s\n", tmp->tag, tmp->value);
	// 	tmp = tmp->next;
	// }
	
	data.ast = parser(&data, data.tokens, find_last_node(data.tokens));
	print_ast(data.ast, 0);
	free_tokens(&data.tokens);
	if (data.ast)
		data.shell->status = execute(data.ast, data.shell);
	free_ast(data.ast);
	return (0);
}
