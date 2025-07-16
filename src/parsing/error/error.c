/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:03:29 by nyousfi           #+#    #+#             */
/*   Updated: 2025/07/03 15:24:48 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	tag_is_operator(t_tag tag)
{
	if (tag == AND)
		return (true);
	if (tag == OR)
		return (true);
	if (tag == PIPE)
		return (true);
	return (false);
}

bool	is_operator_error(t_data *data, t_tag tag)
{
	if (tag_is_operator(tag))
	{
		print_correct_error(tag, data);
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
				print_correct_error(current->next->tag, data);
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
