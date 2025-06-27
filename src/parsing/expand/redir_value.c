/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:20:46 by nass              #+#    #+#             */
/*   Updated: 2025/06/27 17:41:11 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_next_value(t_token *current, t_token *next, t_data *data)
{
	t_token	*tmp;

	if (!next)
	{
		print_correct_error(current->tag);
		free_tokens(&data->tokens);
		data->error = true;
		return ;
	}
	tmp = next->next;
	free(current->value);
	current->value = next->value;
	free(next);
	current->next = tmp;
}

void	change_redir_value(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (current->tag == REDIR_IN || current->tag == REDIR_OUT
			|| current->tag == APPEND || current->tag == HEREDOC)
			get_next_value(current, current->next, data);
		if (data->error == true)
			return ;
		current = current->next;
	}
}
