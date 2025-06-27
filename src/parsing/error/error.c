/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:03:29 by nyousfi           #+#    #+#             */
/*   Updated: 2025/06/27 14:11:35 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	tag_is_operator(t_tag tag)
{
	if (tag == TOKEN_AND)
		return (true);
	if (tag == TOKEN_OR)
		return (true);
	if (tag == TOKEN_PIPE)
		return (true);
	return (false);
}

bool	is_operator_error(t_data *data, t_tag tag)
{
	if (tag_is_operator(tag))
	{
		print_correct_error(tag);
		free_tokens(&data->tokens);
		data->error = true;
		return (true);
	}
	return (false);
}

void	error_checker(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	if (is_operator_error(data, current->tag))
		return ;
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
	if (is_operator_error(data, current->tag))
		return ;
}
