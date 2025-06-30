/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:40:58 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/30 13:44:52 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

bool	is_only_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			i++;
		else
			return (false);
	}
	return (true);
}

t_tag	find_correct_tag(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '&')
		return (AND);
	if (c == '>')
		return (REDIR_OUT);
	if (c == '<')
		return (REDIR_IN);
	if (c == '"')
		return (DOUBLE_QUOTE);
	if (c == '\'')
		return (SINGLE_QUOTE);
	return (WORD);
}

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
