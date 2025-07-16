/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:00:35 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/30 18:15:45 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_quoted_content(t_data *data, char *input, char quote,
		t_double_index id)
{
	char	*content;
	int		len;

	len = id.end - id.start;
	if (id.start == -1 && id.end == -1)
	{
		len = 0;
		content = malloc(1);
		if (content)
			content[0] = 0;
	}
	else
		content = ft_strndup(input + id.start, len);
	if (!content)
	{
		ft_putstr_fd("malloc error\n", STDERR_FILENO);
		free_tokens(&data->tokens);
		return (0);
	}
	if (quote == '"' && id.start != -1 && id.end != -1)
		add_token(&data->tokens, split_tokens(content));
	else
		add_token(&data->tokens, create_token(content, SINGLE_QUOTE));
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
	{
		id.end = -1;
		id.start = -1;
		return (handle_quoted_content(data, input, quote, id));
	}
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] != quote)
	{
		free(input);
		syntax_error(data, "syntax error : unclosed quote\n");
		data->shell->status = 2;
		return (0);
	}
	id.start = start;
	id.end = i;
	return (handle_quoted_content(data, input, quote, id));
}
