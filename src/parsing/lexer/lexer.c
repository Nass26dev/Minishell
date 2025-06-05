/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:05:03 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/05 15:28:04 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/parsing/parsing.h"

bool is_space(char c)
{
	if (c == ' ')
		return (true);
	else if (c == '\t')
		return (true);
	return (false);
}

bool is_operator(char c)
{
	if (c == '<')
		return (true);
	else if (c == '>')
		return (true);
	else if (c == '|')
		return (true);
	else if (c == '&')
		return (true);
	else if (c == '(')
		return (true);
	return (false);
}

bool ft_isalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (true);
	return (false);
}

void lexer(t_data *data, char *input)
{
	int i;

	i = -1;
	(void)data;
	while (input[++i] != 0)
	{
		if (is_space(input[i]))
			continue ;
		else if (input[i] == '"')
			read_double_quoted_string(&data, input, &i);
		else if (input[i] == '\'')
			read_simple_quoted_string(&data, input, &i);
		else if (input[i] == '$')
			read_variable(&data, input, &i);
		else if (is_operator(input[i]))
			read_operator(&data, input, &i);
		else if (ft_isalpha(input[i]))
			read_word(&data, input, &i);
		else if (is_separator(input[i]))
			read_separator(&data, input, &i);
	}
}
