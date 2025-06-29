/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nass <nass@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:20:46 by nass              #+#    #+#             */
/*   Updated: 2025/06/28 13:01:21 by nass             ###   ########.fr       */
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

void	change_heredoc_value(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (current->tag == HEREDOC)
			get_next_value(current, current->next, data);
		if (data->error == true)
			return ;
		current = current->next;
	}
}

void	change_redir_value(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (current->tag == REDIR_IN || current->tag == REDIR_OUT
			|| current->tag == APPEND)
			get_next_value(current, current->next, data);
		if (data->error == true)
			return ;
		current = current->next;
	}
}
