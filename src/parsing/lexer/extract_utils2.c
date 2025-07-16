/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:41:39 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/16 10:16:27 by nyousfi          ###   ########.fr       */
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
		ft_putstr_fd("malloc error\n", STDERR_FILENO);
		free_tokens(&data->tokens);
		return (0);
	}
	add_token(&data->tokens, create_token(content, VARIABLE));
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
		ft_putstr_fd("malloc error\n", STDERR_FILENO);
		free_tokens(&data->tokens);
		return (0);
	}
	add_token(&data->tokens, create_token(content, WORD));
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
		ft_putstr_fd("malloc_error\n", STDERR_FILENO);
		free_tokens(&data->tokens);
		return (0);
	}
	add_token(&data->tokens, create_token(content, WORD));
	free(content);
	return (len);
}
