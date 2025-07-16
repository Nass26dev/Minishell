/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:33:45 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/16 09:18:23 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"

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

bool	else_case(char *input, int *index, t_data *data)
{
	int	i;

	i = *index;
	if (input[i] == '\'')
	{
		i++;
		while (input[i] != '\'' && input[i])
			i++;
	}
	if (input[i] == '<' || input[i] == '>')
	{
		if (input[i + 1] == '|' || input[i + 1] == '&')
		{
			if (input[i + 1] == '|')
				print_correct_error(PIPE, data);
			else if (input[i] == '&' && input[i + 1] == '&')
				print_correct_error(AND, data);
			else if (input[i] == '&')
				print_correct_error(13, data);
			return (true);
		}
	}
	return (false);
}

bool	nb_redir(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '<')
			return (true_exit(REDIR_OUT, data));
		if (input[i] == '<' && input[i + 1] == '>')
			return (true_exit(REDIR_IN, data));
		if (input[i] == '<' || input[i] == '>')
		{
			if (input[i + 1] && (input[i + 1] == '<' || input[i + 1] == '>'))
			{
				if (input[i + 2] && (input[i + 2] == '<' || input[i
							+ 2] == '>'))
					return (true_exit(find_correct_tag(input[i]), data));
			}
		}
		i++;
	}
	return (false);
}

bool	mltpl_check(t_data *data, char *input)
{
	if (!input[0] || is_only_spaces(input) || is_only_quotes(input)
		|| check_redir_error(input, data) || nb_redir(input, data))
	{
		free(input);
		return (true);
	}
	if (lexer_expander_checker(data, input))
		return (true);
	if (!data->tokens->next && !data->tokens->value[0])
	{
		free_tokens(&data->tokens);
		return (true);
	}
	return (false);
}

int	minishell_loop(t_shell *shell)
{
	static t_data	data;
	char			*input;
	int				ret;

	data.heredoc = NULL;
	data.shell = shell;
	ret = get_input_and_add_to_historical(&input);
	if (ret == 1)
		return (1);
	if (ret == 2)
	{
		g_received_signal = 0;
		data.shell->status = 130;
	}
	if (mltpl_check(&data, input))
		return (0);
	if (change_heredoc(&data))
		return (0);
	data.ast = parser(&data, data.tokens, find_last_node(data.tokens));
	free_tokens(&data.tokens);
	if (data.ast)
		data.shell->status = execute(data.ast, data.shell, data.heredoc);
	free_ast(data.ast);
	free_all_heredocs(&data.heredoc);
	return (0);
}
