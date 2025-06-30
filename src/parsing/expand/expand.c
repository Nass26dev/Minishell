/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:18:39 by nass              #+#    #+#             */
/*   Updated: 2025/06/30 13:27:03 by nyousfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*reverse_token_list(t_token *start, t_token *end)
{
	t_token	*prev;
	t_token	*current;
	t_token	*next;
	t_token	*after;

	prev = NULL;
	current = start;
	next = NULL;
	after = end->next;
	while (current != after)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	start->next = after;
	return (prev);
}

void	main_sort(t_token_redir *tr, t_token **head)
{
	if (is_redirection(tr->current->tag))
	{
		tr->redir_start = tr->current;
		tr->redir_end = tr->current;
		while (tr->redir_end->next && is_redirection(tr->redir_end->next->tag))
			tr->redir_end = tr->redir_end->next;
		tr->reversed = reverse_token_list(tr->redir_start, tr->redir_end);
		if (tr->prev)
			tr->prev->next = tr->reversed;
		else
			*head = tr->reversed;
		tr->prev = tr->redir_start;
		tr->current = tr->redir_start->next;
	}
	else
	{
		tr->prev = tr->current;
		tr->current = tr->current->next;
	}
}

void	sort_redirections(t_token **head)
{
	t_token_redir	tr;

	tr.current = *head;
	tr.prev = NULL;
	while (tr.current)
		main_sort(&tr, head);
}

void	move_start_redir(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if (node_is_redir(current) && node_is_word(current->next))
		{
			switch_nodes(current, current->next);
			current = *head;
		}
		else
			current = current->next;
	}
}

t_token *delete_empty_node(t_data *data, t_token *tmp)
{
	t_token *tmp2;

	tmp2 = tmp->next;
	delete_node(&data->tokens, tmp);
	return (tmp2);
}

void concatenate_redirections_args(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		if (node_is_redir(tmp) && tmp->next && !tmp->space)
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

void	expander(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	change_heredoc_value(data);
	t_token *tmp2;
	tmp2 = data->tokens;
	while (tmp2)
	{
		printf("tag = %d, value = '%s', space = %d\n", tmp2->tag, tmp2->value, tmp2->space);
		tmp2 = tmp2->next;
	}
	while (tmp)
	{
		if (tmp->tag == VARIABLE || tmp->tag == DOUBLE_QUOTE
			|| tmp->tag == WORD)
			{
				while (is_var(tmp->value))
			{
				if (expand_token_value(tmp->value, &tmp, data))
				malloc_error(data);
				if (!tmp->value[0])
				tmp = delete_empty_node(data, tmp);
			}
			tmp->tag = WORD;
		}
		tmp = tmp->next;
	}
	change_redir_value(data);
	concatenate_redirections_args(data);
	concatenation(data);
	move_start_redir(&data->tokens);
	sort_redirections(&data->tokens);
	create_cmd(data);
}
