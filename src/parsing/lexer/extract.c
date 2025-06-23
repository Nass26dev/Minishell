/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:56:26 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/23 15:36:17 by nass             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	extract_operator(t_data *data, const char *input, int i)
{
	int	ret;

	ret = 0;
	if (input[i] == '|')
		ret = pipe_or(data, input, i);
	else if (input[i] == '&')
		ret = ampersand(data, (char *)input, i);
	else if (input[i] == '>')
		ret = redir_out_append(data, input, i);
	else if (input[i] == '<')
		ret = redir_in_heredoc(data, input, i);
	return (ret);
}

int	extract_quoted_string(t_data *data, char *input, int i)
{
	char	*content;
	char	quote;
	int		start;
	int		len;

	quote = input[i];
	start = ++i;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] != quote)
	{
		free(input);
		syntax_error(data, "syntax error : unclosed quote");
		return (0);
	}
	len = i - start;
	content = ft_strndup(input + start, len);
	if (quote == '"')
		add_token(&data->tokens, create_token(content, TOKEN_DOUBLE_QUOTE));
	else
		add_token(&data->tokens, create_token(content, TOKEN_SINGLE_QUOTE));
	free(content);
	return (len + 2);
}

int	extract_variable(t_data *data, const char *input, int i)
{
	int		start;
	char	*content;
	int		len;

	start = i;
	i++;
	while (ft_isalnum(input[i]) || input[i] == '_' || input[i] == '?')
		i++;
	len = i - start;
	content = ft_strndup(input + start, len);
	add_token(&data->tokens, create_token(content, TOKEN_VARIABLE));
	free(content);
	return (len);
}

int	extract_word(t_data *data, const char *input, int i)
{
	int		start;
	char	*content;
	int		len;

	start = i;
	while (input[i] && !ft_isspace(input[i]) && !is_operator(input[i])
		&& input[i] != '\'' && input[i] != '"' && input[i] != '$')
		i++;
	len = i - start;
	content = ft_strndup(input + start, i - start);
	add_token(&data->tokens, create_token(content, TOKEN_WORD));
	free(content);
	return (len);
}
