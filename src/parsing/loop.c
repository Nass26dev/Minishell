/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:33:45 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/24 16:06:13 by nyousfi          ###   ########.fr       */
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
	static int		round;

	if (round == 0)
		data.status = 0;
	data.shell = shell;
	if (get_input_and_add_to_historical(&input) == 1)
		return (1);
	lexer(&data, input);
	if (is_error(&data.error))
		return (0);
	free(input);
	printf("exit code %d\n", data.status);
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
	// 		printf("tag = %d, value = %s", tmp->tag);
	// 		int i = 0;
	// 		while (tmp->cmd[i])
	// 			printf(" ", tmp->cmd[i++]);
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
	data.status = data.shell->status;
	printf("|exit code %d\n", data.status);

	free_ast(data.ast);
	round++;
	return (0);
}
