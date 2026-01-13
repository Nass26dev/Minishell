/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:20:46 by nass              #+#    #+#             */
/*   Updated: 2025/07/01 14:18:11 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_next_value(t_token *current, t_token *next, t_data *data)
{
	t_token	*tmp;

	if (!next)
	{
		print_correct_error(current->tag, data);
		free_tokens(&data->tokens);
		data->error = true;
		return ;
	}
	tmp = next->next;
	free(current->value);
	current->space = next->space;
	current->value = next->value;
	free(next);
	current->next = tmp;
}

void	concatenate_heredoc_args(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (tmp->tag == HEREDOC && tmp->next && !tmp->space)
		{
			tmp->value = ft_strjoin(tmp->value, tmp->next->value);
			if (!tmp->value)
				malloc_error(data);
			tmp->space = tmp->next->space;
			delete_node(&data->tokens, tmp->next);
		}
		else
			tmp = tmp->next;
	}
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
	concatenate_heredoc_args(data);
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
