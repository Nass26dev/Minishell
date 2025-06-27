/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:33:45 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 15:17:43 by nyousfi          ###   ########.fr       */
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

int	lexer_expander_checker(t_data *data, char *input)
{
	lexer(data, input);
	if (is_error(&data->error))
		return (1);
	free(input);
	expander(data);
	if (is_error(&data->error))
		return (1);
	error_checker(data);
	if (is_error(&data->error))
		return (1);
	return (0);
}

bool	is_only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else
			return (false);
	}
	return (true);
}

int	minishell_loop(t_shell *shell)
{
	static t_data	data;
	char			*input;
	int				ret;

	data.shell = shell;
	ret = get_input_and_add_to_historical(&input);
	if (ret == 1)
		return (1);
	if (ret == 2)
		data.shell->status = 130;
	if (!input[0] || is_only_spaces(input))
	{
		free(input);
		return (0);
	}
	if (lexer_expander_checker(&data, input))
		return (0);
	data.ast = parser(&data, data.tokens, find_last_node(data.tokens));
	free_tokens(&data.tokens);
	if (data.ast)
		data.shell->status = execute(data.ast, data.shell);
	free_ast(data.ast);
	return (0);
}
