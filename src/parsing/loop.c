/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:33:45 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/25 15:31:22 by nyousfi          ###   ########.fr       */
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

	data.shell = shell;
	
	if (get_input_and_add_to_historical(&input) == 1)
		return (1);
	if (!input[0])
	{
		free(input);
		return (0);
	}
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
	// t_token *tmp = data.tokens;
	// while (tmp)
	// {
	// 	if (tmp->tag == TOKEN_CMD)
	// 	{
	// 		printf("tag = %d, value = %s", tmp->tag, tmp->value);
	// 		int i = 0;
	// 		while (tmp->cmd[i])
	// 			printf("%s ", tmp->cmd[i++]);
	// 		printf("\n");
	// 	}
	// 	else
	// 		printf("tag = %d, value = %s\n", tmp->tag, tmp->value);
	// 	tmp = tmp->next;
	// }
	data.ast = parser(&data, data.tokens, find_last_node(data.tokens));
	// print_ast(data.ast, 0);
	free_tokens(&data.tokens);
	if (data.ast)
		data.shell->status = execute(data.ast, data.shell);
	// int i;
	// i = 0;
	// while (data.shell->env->data[i])
	// {
	// 	printf("%s\n", data.shell->env->data[i]);
	// 	i++;
	// }
	free_ast(data.ast);
	return (0);
}
