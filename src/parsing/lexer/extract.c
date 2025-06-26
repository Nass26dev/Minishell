/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:56:26 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/26 15:15:23 by nass             ###   ########.fr       */
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

t_token	*split_tokens(char *content, t_data *data)
{
	t_token	*head;
	int		i;
	int		start;
	char	*before;
	char	*dollar;
	char	*last;

	head = NULL;
	i = 0;
	start = 0;
	(void)data;
	while (content[i])
	{
		if (content[i] == '$' && (content[i + 1] == '\0' || ft_isspace(content[i
					+ 1]) || content[i + 1] == '$'))
		{
			if (i > start)
			{
				before = ft_substr(content, start, i - start);
				if (before)
				{
					add_token(&head, create_token(before, TOKEN_WORD));
					free(before);
				}
			}
			dollar = ft_substr(content, i, 1);
			if (dollar)
			{
				add_token(&head, create_token(dollar, TOKEN_WORD));
				free(dollar);
			}
			i++;
			start = i;
		}
		else
			i++;
	}
	if (i > start)
	{
		last = ft_substr(content, start, i - start);
		if (last)
		{
			add_token(&head, create_token(last, TOKEN_WORD));
			free(last);
		}
	}
	return (head);
}

int	extract_quoted_string(t_data *data, char *input, int i)
{
	char	*content;
	char	quote;
	int		start;
	int		len;

	quote = input[i];
	start = ++i;
	if (quote == '"' && input[i] == '"')
		return (2);
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
	if (!content)
	{
		printf("malloc error\n");
		free_tokens(&data->tokens);
		return (0);
	}
	if (quote == '"')
		add_token(&data->tokens, split_tokens(content, data));
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
	if (!content)
	{
		printf("malloc error\n");
		free_tokens(&data->tokens);
		return (0);
	}
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
	if (!content)
	{
		printf("malloc error\n");
		free_tokens(&data->tokens);
		return (0);
	}
	add_token(&data->tokens, create_token(content, TOKEN_WORD));
	free(content);
	return (len);
}

int	extract_space(t_data *data, const char *input, int i)
{
	int		start;
	char	*content;
	int		len;

	start = i;
	while (input[i] && ft_isspace(input[i]))
		i++;
	len = i - start;
	content = ft_strndup(input + start, i - start);
	if (!content)
	{
		printf("malloc error\n");
		free_tokens(&data->tokens);
		return (0);
	}
	add_token(&data->tokens, create_token(content, TOKEN_WORD));
	free(content);
	return (len);
}
