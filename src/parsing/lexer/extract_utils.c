/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:40:19 by nass              #+#    #+#             */
/*   Updated: 2025/07/01 14:17:44 by eelissal         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	pipe_or(t_data *data, const char *input, int i)
{
	int	ret;

	ret = 0;
	if (input[i + 1] == '|')
	{
		add_token(&data->tokens, create_token(NULL, OR));
		ret = 2;
	}
	else
	{
		add_token(&data->tokens, create_token(NULL, PIPE));
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
		add_token(&data->tokens, create_token(NULL, AND));
		ret = 2;
	}
	else
	{
		syntax_error(data, "syntax error near unexpected token « & »\n");
		data->shell->status = 2;
	}
	return (ret);
}

int	redir_out_append(t_data *data, const char *input, int i)
{
	int	ret;

	ret = 0;
	if (input[i + 1] == '>')
	{
		add_token(&data->tokens, create_token(">>", APPEND));
		ret = 2;
	}
	else
	{
		add_token(&data->tokens, create_token(">", REDIR_OUT));
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
		add_token(&data->tokens, create_token("<<", HEREDOC));
		ret = 2;
	}
	else
	{
		add_token(&data->tokens, create_token("<", REDIR_IN));
		ret = 1;
	}
	return (ret);
}
