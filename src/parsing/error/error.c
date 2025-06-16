/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:03:29 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/16 18:17:36 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool tag_is_operator(t_type tag)
{
	if (tag == TOKEN_AND)
		return (true);
	if (tag == TOKEN_OR)
		return (true);
	if (tag == TOKEN_PIPE)
		return (true);
    return (false);
}

void print_correct_error(t_type tag)
{
	printf("syntax error near unexpected token « ");
	if (tag == TOKEN_AND)
		printf("&& »\n");
	if (tag == TOKEN_APPEND)
		printf(">> »\n");
	if (tag == TOKEN_HEREDOC)
		printf("<< »\n");
	if (tag == TOKEN_OR)
		printf("|| »\n");
	if (tag == TOKEN_PIPE)
		printf("| »\n");
	if (tag == TOKEN_REDIR_IN)
		printf("< »\n");
	if (tag == TOKEN_REDIR_OUT)
		printf("> »\n");
}

void error_checker(t_data *data)
{
	t_token *current;

	current = data->tokens;
	if (tag_is_operator(current->tag))
	{
		print_correct_error(current->tag);
		free_tokens(&data->tokens);
		data->error = true;
		return ;
	}
	while (current->next)
	{
		if (tag_is_operator(current->tag) && current->next)
		{
			if (tag_is_operator(current->next->tag))
			{
				print_correct_error(current->next->tag);
				free_tokens(&data->tokens);
				data->error = true;
				return ;
			}
		}
		current = current->next;
	}
	if (tag_is_operator(current->tag))
	{
		print_correct_error(current->tag);
		free_tokens(&data->tokens);
		data->error = true;
		return ;
	}
}

void syntax_error(t_data *data, char *error)
{
	free_tokens(&data->tokens);
	printf("%s\n", error);
	data->error = true;
}
