/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:05:03 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/16 11:08:53 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	lexer_error(t_data *data)
{
	int	status;

	status = data->shell->status;
	free_shell(data->shell);
	rl_clear_history();
	exit(status);
}

void	lexer(t_data *data, char *input)
{
	int	i;

	i = 0;
	while (input[i] != 0)
	{
		while (ft_isspace(input[i]))
		{
			set_space_to_token(&data->tokens);
			i++;
		}
		if (input[i] == 0)
			break ;
		if (is_operator(input[i]))
			i += extract_operator(data, input, i);
		else if (input[i] == '\'' || input[i] == '"')
			i += extract_quoted_string(data, input, i);
		else if (input[i] == '$')
			i += extract_variable(data, input, i);
		else
			i += extract_word(data, input, i);
		if (data->error == true)
			return ;
		if (!data->tokens)
			lexer_error(data);
	}
}
