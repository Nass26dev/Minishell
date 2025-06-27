/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:00:35 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 16:05:52 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_quoted_content(t_data *data, char *input, char quote,
		t_double_index id)
{
	char	*content;
	int		len;

	len = id.end - id.start;
	content = ft_strndup(input + id.start, len);
	if (!content)
	{
		ft_putstr_fd("malloc error\n", STDERR_FILENO);
		free_tokens(&data->tokens);
		return (0);
	}
	if (quote == '"')
		add_token(&data->tokens, split_tokens(content));
	else
		add_token(&data->tokens, create_token(content, TOKEN_SINGLE_QUOTE));
	free(content);
	return (len + 2);
}

int	extract_quoted_string(t_data *data, char *input, int i)
{
	char			quote;
	int				start;
	t_double_index	id;

	quote = input[i];
	start = ++i;
	if (quote == '"' && input[i] == '"')
		return (2);
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] != quote)
	{
		free(input);
		syntax_error(data, "syntax error : unclosed quote\n");
		return (0);
	}
	id.start = start;
	id.end = i;
	return (handle_quoted_content(data, input, quote, id));
}
