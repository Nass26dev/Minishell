/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:40:19 by nass              #+#    #+#             */
/*   Updated: 2025/06/19 17:39:41 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	pipe_or(t_data *data, const char *input, int i)
{
	int	ret;

	ret = 0;
	if (input[i + 1] == '|')
	{
		add_token(&data->tokens, create_token(NULL, TOKEN_OR));
		ret = 2;
	}
	else
	{
		add_token(&data->tokens, create_token(NULL, TOKEN_PIPE));
		ret = 1;
	}
	return (ret);
}

int	ampersand(t_data *data, char *input, int i)
{
	int	ret;

	ret = 0;
	if (input[i + 1] == '&')
	{
		add_token(&data->tokens, create_token(NULL, TOKEN_AND));
		ret = 2;
	}
	else
		syntax_error(data, "syntax error near unexpected token « & »");
	return (ret);
}

int	redir_out_append(t_data *data, const char *input, int i)
{
	int	ret;

	ret = 0;
	if (input[i + 1] == '>')
	{
		add_token(&data->tokens, create_token(">>", TOKEN_APPEND));
		ret = 2;
	}
	else
	{
		add_token(&data->tokens, create_token(">", TOKEN_REDIR_OUT));
		ret = 1;
	}
	return (ret);
}

int	redir_in_heredoc(t_data *data, const char *input, int i)
{
	int	ret;

	ret = 0;
	if (input[i + 1] == '<')
	{
		add_token(&data->tokens, create_token("<<", TOKEN_HEREDOC));
		ret = 2;
	}
	else
	{
		add_token(&data->tokens, create_token("<", TOKEN_REDIR_IN));
		ret = 1;
	}
	return (ret);
}
